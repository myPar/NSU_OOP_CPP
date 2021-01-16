#pragma once
#include "Block.h"

class WriteFile : public Block {
private:
	Node node;
	// private constructor
	WriteFile(Node node);
public:
	optional<vector<string>> *execute(optional<vector<string>> *input) override;
	friend Block* Block::factory_method(const Node node);
};
