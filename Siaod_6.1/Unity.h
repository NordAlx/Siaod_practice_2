#pragma once

#include "BinaryFile.h"
#include "HashTable.h"

namespace Unity {
	void startWork();
	void dlt(string key, HashTable* table, Elements* fileElements, string name);
	void findInFile(string key, HashTable* table, Elements* fileElements, string name);
} // namespace

