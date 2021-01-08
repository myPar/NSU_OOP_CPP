#include "Block.h"
#include "ReadFile.h"
#include "WriteFile.h"
#include "Grep.h"
#include "Sort.h"
#include "Replace.h"
#include "Dump.h"

using namespace WorkflowSpec;

Block* Block::factory_method(const Node node) {
	string name = node.get_name();

	if (name == names[0]) {
		return static_cast<Block*>(new ReadFile(node));
	}
	if (name == names[1]) {
		return static_cast<Block*>(new WriteFile(node));
	}
	if (name == names[2]) {
		return static_cast<Block*>(new Grep(node));
	}
	if (name == names[3]) {
		return static_cast<Block*>(new Sort(node));
	}
	if (name == names[4]) {
		return static_cast<Block*>(new Replace(node));
	}
	if (name == names[5]) {
		return static_cast<Block*>(new Dump(node));
	}
	assert(0 && "invalid block name");
}
