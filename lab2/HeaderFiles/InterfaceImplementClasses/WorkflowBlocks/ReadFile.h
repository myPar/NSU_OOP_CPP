#pragma once
#include "Block.h"
#include <string>

class ReadFile : public Block {
private:
	Node node;
	// private constructor
	ReadFile(Node node);
public:
	optional<vector<string>> *execute(optional<vector<string>> *input) override;
	friend Block* Block::factory_method(Node node);
};
