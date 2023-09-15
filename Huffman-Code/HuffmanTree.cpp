/*Uliana Ozerova, U17965448*/

#include "HuffmanTree.hpp"
#include <map>
#include <stack>

std::string HuffmanTree::compress(const std::string inputStr) {

	/*generate a map char/freq*/
	std::map <char, int> freq_char_map;
	std::map <char, int>::iterator it;

	for (size_t i = 0; i < inputStr.size(); i++) {
		freq_char_map[inputStr[i]] += 1;
	}

	/*check mapped values
	std::cout << "Mapped:\n";
	for (it = freq_char_map.begin(); it != freq_char_map.end(); it++) {
		std::cout << it->first << " = " << it->second << '\n';
	} */

	/*inserting pairs into the queue: first - char, second - freq; */

	HeapQueue<HuffmanNode*, HuffmanNode::Compare> queue;
	
	for (it = freq_char_map.begin(); it != freq_char_map.end(); it++) {
		HuffmanNode* new_pair_node;
		new_pair_node = new HuffmanNode(it->first, it->second);
		queue.insert(new_pair_node);
	} 
	/*storing 2 smallest char/freq node pairs to temp, sum their frequencies, make a parent node with fre1+freq2
			temp_first = min1 = left child,
			temp_second = min2 = right child
			parent = freq of left + freq of right*/

	while (queue.size() > 1) {
	
		HuffmanNode* temp_first = queue.min();
		queue.removeMin();

		HuffmanNode* temp_second = queue.min();
		queue.removeMin();

	/*creating a new frequency for the parent */
		size_t new_freq = temp_first->getFrequency() + temp_second->getFrequency();

	/*creating a parent by using the constructor with children*/
		HuffmanNode* intermediate_parent = new HuffmanNode('\0', new_freq, nullptr, temp_first, temp_second); //no parent of the parent

    /* put that intermediate node back in the priority queue*/
		queue.insert(intermediate_parent);
	}

	/*only root is left in the queue*/
	tree_node = queue.min();

	std::map <char, std::string> cbMap;
	std::string string_to_pass = ""; //for use in preorderTraversal

	preorderTraversal(queue.min(), string_to_pass, cbMap); //passing by reference

	std::string encoded = "";

	/*catching*/
	for (size_t i = 0; i < inputStr.size(); i++) {
		encoded = encoded + cbMap[inputStr[i]]; 
	}
	return encoded;
}

	/*only leaves have characters in them*/
void HuffmanTree::preorderTraversal(HuffmanNode * node, std::string resulting_string, std::map <char, std::string>& cbMap) {
	if (node == nullptr)
		return;

	if (node->isLeaf()) { 
		cbMap.insert(std::pair <char, std::string>(node->getCharacter(), resulting_string));
	}
	else {
		preorderTraversal(node->left, resulting_string + "0", cbMap);
		preorderTraversal(node->right, resulting_string + "1", cbMap);
	}

	         //std::cout << resulting_string;
}

	//serializing using postorder traversal: children before the parent
std::string HuffmanTree::help_serialize(HuffmanNode* pnode) {
		std::string result = "";

		if (pnode->isBranch()) {
			result = result + help_serialize(pnode->left);
			result = result + help_serialize(pnode->right) + "B";
			return result;
		}

		else {
			//std::cout << "node: " << tree_node->getCharacter() << "\n";
			result = result + "L" + pnode->getCharacter();
			//std::cout << pnode->left->getCharacter() << "\t" << pnode->right->getCharacter();
			return result;
		}
	} 

std::string HuffmanTree::serializeTree() const {
		HuffmanTree t;
		std::string result;
		result = t.help_serialize(tree_node);

		return result;
	}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {

/*going from postorder back to the tree: L LdLgBLhLmBBLpLxBLfBBLiBBLeLsLbBLaBBLcLoBLlBLnLtBBBB*/

		for (size_t i = 0; i < serializedTree.length();) {

			if (serializedTree[i] == 'L') {
				//if L, getting the character right after by updating i
			    i=i+1;      
				HuffmanNode* temp = new HuffmanNode(serializedTree[i], 0); //frequency doesn`t matter
				s.push(temp);
			}

			else if (serializedTree[i] == 'B'){

				//LIFO, right-last
				HuffmanNode* right = s.top();
				s.pop(); 

				HuffmanNode* left = s.top();
				s.pop(); 
				HuffmanNode* new_parent = new HuffmanNode('\0', 0, nullptr, left, right); //only leaves have characters

				//std::cout << " PARENT" << '\n' << new_parent->left->getCharacter() << '\t' << new_parent->right->getCharacter() << '\n';

				s.push(new_parent);
			}
			i++;
		}

		std::string resulting_string = ""; 

		//the last character is in the root

		resulting_string = binary_decode(inputCode);
		return resulting_string;
	}
 
std::string HuffmanTree::binary_decode(std::string inCode) {

		HuffmanNode* current = s.top(); //curent node is the tree root 
		std::string resultin = "";

		for (size_t i = 0; i < inCode.length() + 1; ) {

			//if node is a leaf, get the character
			if (current == nullptr) {
				break;
			}
			if (current->isLeaf()) {
				resultin = resultin + current->getCharacter();
				current = s.top(); //getting back to the root
			}

			else if (current->isBranch()) {
				if (inCode[i] == '0') {
					current = current->left;
				}
				else if (inCode[i] == '1') {
					current = current->right;
				}
				i++;
			}		
		}
		return resultin;

	}
/*int main() {

	HuffmanTree t;

	std::string text = "if a machine is expected to be infallible it cannot also be intelligent";
	std::string result, result1, result2, result3, serialized;
	result = t.compress(text);
	//std::cout << "text     :   " << text << std::endl;
	//std::cout << "encoded  :   " << result << std::endl;
	std::string code = "0110101100101100010011101111000010010011111010000011101000010001010101010010011000111110001000000111111001001010110000011111001011101111011101011101011101100000111111001100010111110111011001111100101111011010011001001010110000011111011111001101110101101000110011101111";
	serialized = t.serializeTree();
	std::cout << "serialized:   " << result1 << std::endl;
	std::string decoded = t.decompress(code, serialized);
	std::cout << "decoded:   " << decoded << std::endl;

	//std::string text2 = "In computer science and information theory, a Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. The process of finding and/or using such a code proceeds by means of Huffman coding, an algorithm developed by David A. Huffman while he was a Sc.D. student at MIT, and published in the 1952 paper \"A Method for the Construction of Minimum-Redundancy Codes\". The output from Huffman's algorithm can be viewed as a variable-length code table for encoding a source symbol (such as a character in a file). The algorithm derives this table from the estimated probability or frequency of occurrence (weight) for each possible value of the source symbol. As in other entropy encoding methods, more common symbols are generally represented using fewer bits than less common symbols. Huffman's method can be efficiently implemented, finding a code in time linear to the number of input weights if these weights are sorted. However, although optimal among methods encoding symbols separately, Huffman coding is not always optimal among all compression methods.";
	//result2 = t.compress(text2);
	result3 = t.serializeTree();
	//std::cout << "text2     :   " << text2 << std::endl;
	//std::cout << "encoded2  :   " << result2 << std::endl;
	std::cout << "serialized:   " << result3 << std::endl;
	return 0;
} */