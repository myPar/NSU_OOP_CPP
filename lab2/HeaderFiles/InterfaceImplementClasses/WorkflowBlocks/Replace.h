#pragma once
#include "Block.h"

class Replace : public Block {
private:
	Node node;
	// private constructor
	Replace(Node node);
public:
	optional<vector<string>> *execute(optional<vector<string>> *input) override;
	void Delete() override;
	friend Block* Block::factory_method(Node node);
};
