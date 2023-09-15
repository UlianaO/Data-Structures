#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <cstddef>
#include <string>
#include <iostream>
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <stack>

//#include "TestStrings.hpp"

/*HuffmanNode(char c, size_t f, HuffmanNode *p, HuffmanNode *l, HuffmanNode *r) 
: character(c), frequency(f), parent(p), left(l), right(r) {};
  HuffmanNode(char c, size_t f) 
  : HuffmanNode(c, f, nullptr, nullptr, nullptr) {};
  
  a node stores char and frequency as a pair.*/

class HuffmanTree : public HuffmanTreeBase {
public:
	std::string compress(const std::string inputStr);
	std::string serializeTree() const;
	std::string help_serialize(HuffmanNode* pnode);
	std::string decompress(const std::string inputCode, const std::string serializedTree);
	void preorderTraversal(HuffmanNode* node, std::string result_string, std::map <char, std::string>& cbMap);
	//void preorderTraversal(std::map <char, std::string>* char_binary_code, HuffmanNode* node, std::string store_string);
	std::string binary_decode(std::string inCode);
private:
	HuffmanNode* tree_node = nullptr;
	HuffmanNode* root_node;
	std::stack<HuffmanNode*> s;
};

#endif