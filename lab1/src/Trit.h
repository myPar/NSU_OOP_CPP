#pragma once
#include <cstdint>
#include <unordered_map>

using namespace std;

// named constants
enum { byte_size = 8, trit_size = 2, int32_size = sizeof(int32_t) * byte_size };

//Trit enum
enum Trit {
	Unknown,
	True,
	False,
};
// binary operations on Trits
Trit AND(Trit trit1, Trit trit2);
Trit OR(Trit trit1, Trit trit2);
Trit NOT(Trit trit);

class TritSet {
	// class position (save viewing of int block value (S))
	class Position {
	public:
		size_t block_idx;
		size_t bit_pos;
		Position(size_t bl_idx, size_t b_pos);
	};
	// class SetModify (store const ptr on TritSet to modify it)
	class SetModify {
	public:
		// for set modification
		TritSet* const reference;
		Position position;
		size_t init_idx;

		SetModify(TritSet* ref, Position pos, size_t idx);
		void operator= (Trit);
		bool operator==(Trit);
	};
private:
	// integer set
	int32_t* int_set;
	// size of allocated memory in int blocks
	size_t capacity;
	// last trit set idx
	size_t bound_idx;
	// index of last defined trit (Trit index, like: trit_set[idx])
	size_t last_idx;

	// gets trit value
	Trit get_value(Position position) const;
	// sets trit value in the position of the trit set
	void set_value(Position pos, Trit trit);
	// gets trit position by its index
	Position get_position(size_t trit_idx) const;
	// reallocation memory for trit set
	void set_memory_realloc(size_t en_idx);
	// null bits in int block from start idx to end
	void null_bits(size_t start_idx, int32_t* block_ref);
	// masks TritSet with mask using parameterized binary operation
	TritSet masking(const TritSet mask, Trit(* const operation_ptr)(Trit, Trit)) const;
	// inverts TritSet values using binary NOT
	TritSet masking_NOT() const;
public:
	//public methods:
		// constructor
	TritSet(size_t size);
	// copy-constructor
	TritSet(const TritSet&);
	// destructor
	~TritSet();
	// fields getters methods (for Testing only)
	size_t get_capacity() const;
	size_t get_bound_idx() const;
	size_t get_last_idx() const;

	//free memory to last installed trit
	void shrink();
	// returns last not Unknown trit index
	size_t length();
	// forget data of all Trits which are started from idx position
	void trim(size_t idx);
	// returns number of such such type trits
	size_t cardinality(Trit trit);
	// the as 'cardinality' method, but for all Trit types
	unordered_map<Trit, size_t> cardinality();
	// print TritSet data mathod
	void print_data();
	// printing bits of the TritSet
	void print_binary_data();

	// overloaded operators:

	// access to trit by index (for initialising and getting data)
	SetModify operator[] (size_t);
	// overloaded AND
	TritSet operator& (const TritSet);
	// overloaded OR
	TritSet operator| (const TritSet);
	// overloaded NOT
	TritSet operator!();
};
