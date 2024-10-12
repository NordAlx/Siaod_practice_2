#pragma once

#include "BinaryFile.h"
#include "HashTable.h"
using namespace BinaryFuncs;

namespace Unity {
	void startWork();
	void dlt(string key, HashTable& table, string name);
	void findInFile(string key, HashTable& table, string name);
} // namespace

