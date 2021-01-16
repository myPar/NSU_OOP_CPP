#include "pch.h"
#include "Trit.h"
#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>

// constructors and destructors implementation:
	// constructor (TritSet)
TritSet::TritSet(size_t size) {
	assert(size > 0 && "trit set size must be greater then zero");
	size_t bit_number = size * trit_size;

	capacity = bit_number / int32_size;
	last_idx = 0;

	if (bit_number % int32_size != 0) {
		// add one int block if bit number doesn't devide on int32 size
		capacity++;
	}
	// initialize set bound idx
	bound_idx = capacity * int32_size / trit_size - 1;
	// initialize int set
	int_set = new int32_t[capacity]();
}
// copy constructor(TritSet) (creates new int32_t array and copies data from src int32_t array)
TritSet::TritSet(const TritSet& src) : capacity(src.capacity), bound_idx(src.bound_idx), last_idx(src.last_idx) {
	// make new int set
	int_set = new int32_t[capacity];
	// copying data
	for (size_t i = 0; i < capacity; i++) {
		int_set[i] = src.int_set[i];
	}
}
// constructor (Position)
TritSet::Position::Position(size_t b_idx, size_t b_pos) {
	block_idx = b_idx;
	bit_pos = b_pos;
}
// constructor (BlockReference)
TritSet::SetModify::SetModify(TritSet &ref, Position pos, size_t idx) : reference(ref), position(pos), init_idx(idx) {}

// constructor (IterTrit)
TritSet::IterTrit::IterTrit(Trit t, size_t i, const TritSet& ref) : trit(t), idx(i), reference(ref) {}

// destructor (TritSet)
TritSet::~TritSet() {
	delete[] int_set;
}
// private methods:
	// get Trit value
Trit TritSet::get_value(Position pos) const {
	int32_t block = int_set[pos.block_idx];
	size_t bit_pos = pos.bit_pos;

	int bit1 = ((block & (1 << bit_pos)) != 0);
	int bit2 = ((block & (1 << (++bit_pos))) != 0);

	if (bit1 == 0 && bit2 == 0) {
		return Unknown;
	}
	else if (bit1 == 0 && bit2 == 1) {
		return True;
	}
	else if (bit1 == 1 && bit2 == 0) {
		return False;
	}
	else {
		assert(0 && "invalid Trit value\n");
	}
}
// set Trit value
void TritSet::set_value(Position pos, Trit trit) {
	// null trit in bit_pos position before initialization
	int32_t mask = 0;
	mask |= (1 << pos.bit_pos);
	mask |= (1 << (pos.bit_pos + 1));
	mask = ~mask;
	int_set[pos.block_idx] &= mask;

	switch (trit) {
	case True:
		int_set[pos.block_idx] |= (1 << (pos.bit_pos + 1));
		break;
	case False:
		int_set[pos.block_idx] |= (1 << pos.bit_pos);
		break;
	case Unknown:
	{
		break;
	}
	default:
		assert(0 && "invalid Trit type");
	}
}
// get Trit position by its index
TritSet::Position TritSet::get_position(size_t trit_idx) const {
	size_t bit_number = (trit_idx + 1) * trit_size;
	size_t block_idx;
	size_t bit_idx;
	size_t reminder = bit_number % int32_size;

	if (reminder != 0) {
		// set int block idx
		block_idx = bit_number / int32_size;
		// set Trit start bit idx
		bit_idx = reminder - trit_size;
	}
	else {
		// set int block idx
		block_idx = bit_number / int32_size - 1;
		// set Trit start bit idx
		bit_idx = int32_size - trit_size;
	}
	Position trit_pos = Position(block_idx, bit_idx);

	return trit_pos;
}
// trit set memory reallocation
void TritSet::set_memory_realloc(size_t en_idx) {
	Position new_pos = get_position(en_idx);
	Position pos = get_position(last_idx);
	// set default value for new int set
	int32_t* new_int_set = int_set;

	// allocation/free memory case
	if (new_pos.block_idx != capacity - 1) {
		size_t data_bound_idx = en_idx > last_idx ? pos.block_idx : new_pos.block_idx;
		new_int_set = new int32_t[new_pos.block_idx + 1];

		// copy data
		for (size_t i = 0; i <= pos.block_idx; i++) {
			new_int_set[i] = int_set[i];
		}
		// delete old trit set
		delete[] int_set;
		// set to remaining trits default (Unknown) value
		for (size_t i = pos.block_idx + 1; i <= new_pos.block_idx; i++) {
			new_int_set[i] = 0;
		}
	}
	// null the remaining bits in the bound block
	null_bits(new_pos.bit_pos, &new_int_set[new_pos.block_idx]);
	// update trit set fields
	int_set = new_int_set;
	capacity = new_pos.block_idx + 1;
	bound_idx = capacity * int32_size / trit_size - 1;
}
// null bits method implementation
void TritSet::null_bits(size_t start_idx, int32_t* block_ref) {
	int32_t mask = 0;

	for (size_t i = 0; i <= start_idx; i++) {
		mask |= (1 << i);
	}
	(*block_ref) &= mask;
}
// masking function with parameterized binary operation
TritSet TritSet::masking(const TritSet mask, Trit(* const operation_ptr)(Trit, Trit)) const {
	size_t mask_boud_idx = mask.last_idx;
	TritSet result(last_idx + 1);
	// AND template Trits with mask Trits
	for (size_t i = 0; i <= mask_boud_idx; i++) {
		Position pos = get_position(i);

		Trit mask_trit = mask.get_value(pos);
		Trit temp_trit = get_value(pos);

		result[i] = operation_ptr(mask_trit, temp_trit);
	}
	// AND remaining template Trits with UNKNOWN Trits
	for (size_t i = mask_boud_idx + 1; i <= last_idx; i++) {
		Position pos = get_position(i);
		Trit trit = get_value(pos);

		result[i] = operation_ptr(trit, Unknown);
	}

	return TritSet(result);
}

// overloaded operators:
// operator [] for modification and comparing data
TritSet::SetModify TritSet::operator[] (size_t idx) {
	Position trit_pos = get_position(idx);
	// give itself trit set ptr as SetModify constructor parameter
	SetModify ref(*this, trit_pos, idx);

	return ref;
}
// operator = for Trit initializing
void TritSet::SetModify::operator=(Trit trit) {
	// initializing inside trit set
	if (init_idx <= reference.last_idx) {
		reference.set_value(position, trit);
	}
	// initialising with last_idx update (no memory reallocation)
	else if (init_idx > reference.last_idx && init_idx <= reference.bound_idx) {
		reference.set_value(position, trit);
		reference.last_idx = init_idx;
	}
	// out of trit set bound initialising (memory reallocation)
	else if (init_idx > reference.bound_idx) {
		// don't allocate memory with out of bound initializing by Unknown trit
		if (trit != Unknown) {
			// reallocating memory for the trit set and copy existing data
			reference.set_memory_realloc(init_idx);
			reference.set_value(position, trit);
			reference.last_idx = init_idx;
		}
	}
	else {
		assert(0 && "invalid index range");
	}
}
// operator == for Trit comparing
bool TritSet::SetModify::operator==(Trit value) {
	Trit trit = Unknown;

	if (init_idx <= reference.last_idx) {
		trit = reference.get_value(position);
	}
	return trit == value;
}
//operator AND
TritSet TritSet::operator& (const TritSet set) {
	// is left set bigger then rigth
	bool is_max_set = last_idx >= set.last_idx ? true : false;

	if (is_max_set) {
		return masking(set, AND);
	}
	else {
		return set.masking(*this, AND);
	}
}
// operator OR	
TritSet TritSet::operator| (const TritSet set) {
	// is left set bigger then rigth
	bool is_max_set = last_idx >= set.last_idx ? true : false;

	if (is_max_set) {
		return masking(set, OR);
	}
	else {
		return set.masking(*this, OR);
	}
}
//operator NOT
TritSet TritSet::operator!() {
	TritSet result(last_idx + 1);

	for (size_t i = 0; i <= last_idx; i++) {
		Position pos = get_position(i);
		Trit trit = get_value(pos);

		result[i] = NOT(trit);
	}
	return result;
}
// binary operations implementation:
	// operation AND
Trit AND(Trit trit1, Trit trit2) {
	if (trit1 == False || trit2 == False) {
		return False;
	}
	if (trit1 == Unknown || trit2 == Unknown) {
		return Unknown;
	}
	return True;
}
// operation OR
Trit OR(Trit trit1, Trit trit2) {
	if (trit1 == True || trit2 == True) {
		return True;
	}
	if (trit1 == Unknown || trit2 == Unknown) {
		return Unknown;
	}
	return False;
}
// operation NOT
Trit NOT(Trit trit) {
	if (trit == True) {
		return False;
	}
	if (trit == False) {
		return True;
	}
	return Unknown;
}
// public functions:
	// shrink() method implementation
void TritSet::shrink() {
	set_memory_realloc(last_idx);
}
// length() method implementation
size_t TritSet::length() {
	size_t length = -1;			// UNSIGNED_MAX_VALUE = 0 - 1

	for (size_t i = 0; i <= last_idx; i++) {
		Position pos = this->get_position(i);
		Trit trit = this->get_value(pos);

		if (trit != Unknown) {
			length = i;
		}
	}
	return ++length;
}
// trim() method implementation
void TritSet::trim(size_t idx) {
	for (size_t i = idx; i <= last_idx; i++) {
		(*this)[i] = Unknown;
	}
}
// cardinality() method implementation
size_t TritSet::cardinality(Trit trit) {
	size_t count = 0;

	for (size_t i = 0; i <= last_idx; i++) {
		Position pos = this->get_position(i);
		Trit cur_trit = this->get_value(pos);

		if (cur_trit == trit) {
			count++;
		}
	}
	return count;
}
// cardinality() method for all Trit types implementation
unordered_map<Trit, size_t> TritSet::cardinality() {
	unordered_map<Trit, size_t> map;
	pair<Trit, size_t> true_pair(True, 0);
	pair<Trit, size_t> false_pair(False, 0);
	pair<Trit, size_t> unknown_pair(Unknown, 0);

	map.insert(true_pair);
	map.insert(false_pair);
	map.insert(unknown_pair);

	for (size_t i = 0; i <= last_idx; i++) {
		Position pos = this->get_position(i);
		Trit trit = this->get_value(pos);

		map[trit]++;
	}
	return map;
}

// print TritSet data methods:
void TritSet::print_binary_data() {
	for (size_t block_idx = 0; block_idx < capacity; block_idx++) {
		for (size_t bit_pos = 0; bit_pos < int32_size; bit_pos++) {
			int32_t block = int_set[block_idx];

			if ((block & (1 << bit_pos)) != 0) {
				cout << '1';
			}
			else {
				cout << '0';
			}
			if (bit_pos % trit_size == trit_size - 1) {
				cout << " ";
			}
		}
		cout << "| ";
	}
	cout << endl;
}

void TritSet::print_data() {
	cout << "fields:" << endl;
	cout << "	capacity: " << capacity << endl;
	cout << "	last_idx: " << last_idx << endl;
	cout << "	bound_idx: " << bound_idx << endl;
	cout << "data: " << endl;
	print_binary_data();
	cout << endl;
}

// fields getters methods:
size_t TritSet::get_capacity()  const { return capacity; }
size_t TritSet::get_bound_idx() const { return bound_idx; }
size_t TritSet::get_last_idx() const { return last_idx; }

// iterator implementation:
	// iterator begin() method
TritSet::iterator TritSet::begin() {
	Position begin_position = get_position(0);
	Trit trit = get_value(begin_position);

	return iterator(trit, 0, *this);
}
	// iterator end() method
TritSet::iterator TritSet::end() {
	Trit trit = Unknown;

	return iterator(trit, last_idx + 1, *this);
}
	// overloaded operator++
void TritSet::IterTrit::operator++() {
	// update idx
	idx++;
	Position pos = reference.get_position(idx);
	Trit t = reference.get_value(pos);
	// update trit
	trit = t;
}
	// overloaded operator!=
bool TritSet::IterTrit::operator!=(IterTrit arg) {
	if (idx != arg.idx) {
		return true;
	}
	return false;
}
	// overloaded operator*
Trit TritSet::IterTrit::operator*() {
	return trit;
}
