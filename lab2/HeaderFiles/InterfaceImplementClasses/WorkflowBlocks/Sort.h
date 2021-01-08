#pragma once
#include <map>
#include "Block.h"

class Sort : public Block {
private:
	Node node;
	// private constructor
	Sort(Node node);
public:
	optional<vector<string>> *execute(optional<vector<string>> *input) override;
	void Delete() override;
	friend Block* Block::factory_method(Node node);
};
