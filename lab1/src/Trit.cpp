#include "Trit.h"
#include <string>
#include <cassert>
#include <iostream>

// named constants
enum { byte_size = 8, trit_size = 2, int32_size = sizeof(int32_t) * byte_size };

// methods declaration
	// constructor (TritSet)
TritSet::TritSet(size_t size) {
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
	int_set = new int32_t[capacity];

	for (size_t i = 0; i < capacity; i++) {
		// null bits in block
		int_set[i] = 0;
	}
}

	// constructor (Position)
TritSet::Position::Position(size_t b_idx, size_t b_pos) {
	block_idx = b_idx;
	bit_pos = b_pos;
}
	// constructor (BlockReference)
TritSet::SetModify::SetModify(TritSet *ref, Position pos, size_t idx) : reference(ref), position(pos), init_idx(idx) {}

	// destructor (TritSet)
TritSet::~TritSet() {
	delete[] int_set;
}
	// get Trit value
Trit TritSet::get_value(Position pos) const{
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
	switch (trit) {
	case True: 
		int_set[pos.block_idx] |= (1 << (pos.bit_pos + 1));
		break;
	case False:
		int_set[pos.block_idx] |= (1 << pos.bit_pos);
		break;
	case Unknown:
	{
		int32_t mask = 0;
		mask |= (1 << pos.bit_pos);
		mask |= (1 << (pos.bit_pos + 1));
		mask = ~mask;
		// null trit in bit_pos position
		int_set[pos.block_idx] &= mask;
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
	if (new_pos.block_idx != pos.block_idx) {
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
// overloaded operators
	// operator [] for comparing
Trit TritSet::operator[] (size_t idx) const {
	// check if we try to compare trits out of trit set bounds
	if (idx > last_idx) {
		return Unknown;
	}
	Position trit_pos = get_position(idx);

	return get_value(trit_pos);
}
	// operator [] for modification
TritSet::SetModify TritSet::operator[] (size_t idx) {
	Position trit_pos = get_position(idx);
	// give itself trit set ptr as SetModify constructor parameter
	SetModify ref(this, trit_pos, idx);

	return ref;
}
	// operator = for Trit initializing
void TritSet::SetModify::operator=(Trit trit) {
	// initializing inside trit set
	if (init_idx <= reference->last_idx) {
		reference->set_value(position, trit);
	}
	// initialising with last_idx update (no memory reallocation)
	else if (init_idx > reference->last_idx && init_idx <= reference->bound_idx) {
		reference->set_value(position, trit);
		reference->last_idx = init_idx;
	}
	// out of trit set bound initialising (memory reallocation)
	else if (init_idx > reference->bound_idx) {
		// don't allocate memory with out of bound initializing by Unknown trit
		if (trit != Unknown) {
			// reallocating memory for the trit set and copy existing data
			reference->set_memory_realloc(init_idx);
		}
	}
	else {
		assert(0 && "invalid index range");
	}
}
