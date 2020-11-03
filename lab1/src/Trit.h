#pragma once
#include <cstdint>
using namespace std;

//Trit enum
enum Trit {
	Unknown,
	True,
	False,
};

class TritSet {
	// class position (save viewing of int block value (S))
	class Position {
	public:
		size_t block_idx;
		size_t bit_pos;
		Position(size_t bl_idx, size_t b_pos);
	};
	class SetModify {
	public:
		// for set modification
		TritSet *const reference;
		Position position;
		size_t init_idx;

		SetModify(TritSet *ref, Position pos, size_t idx);
		void operator= (Trit);
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

	// run through all set and search last not Unknown trit
	size_t length();
	// gets trit value
    Trit get_value(Position position) const;
	// sets trit value in the position of the trit set
	void set_value(Position pos, Trit trit);
	// gets trit position by its index
	Position get_position(size_t trit_idx) const;
	// reallocation memory for trit set
	void set_memory_realloc(size_t en_idx);
public:
//public methods:
	// constructor
	TritSet(size_t size);
	// destructor
	~TritSet();

	//free memory to last not unknown trit
	void shrink();
	// set all trits from start idx to Unknown value
	void clear_set(size_t start_idx);
	// returns count of such trit value in the set
	size_t get_trit_count(Trit trit);
// get methods
	// returns 'capacity' field value
	size_t get_capacity();
	// returns 'last_idx' field
	size_t get_last_idx();
// overloaded operators
	// access to trit by index (for comparing only)
	Trit operator[] (size_t) const;
	// access to trit by index (for initialising)
	SetModify operator[] (size_t);
};
