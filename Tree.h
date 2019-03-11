#pragma once
#include <forward_list>
#include <tuple>

class LeafNode;
class InnerNode;

class Tree
{
	friend class Node;
	public:
	Tree(size_t = 3, size_t = 3);   //defualt cchldsInNode, ckeysLeafNode
	~Tree();

	public:
	void InsertNextKey(int);   //put the next key in correct position

	public:
	std::tuple<int, int> GetNodeNum();
	void PrintTree();    //output the tree

	private:
	InnerNode *m_pnodeRoot;    //the root of the tree is a InnerNode
	size_t cchldsInNode, ckeysLeafNode;    //the number of childs of inner node cchldsInNode

	//the m_pleafNodeAfter is succeed by m_pleafNodeInserted who is to be inserted in  this forward_list
	LeafNode *m_pleafNodeAfter, *m_pleafNodeInserted; 

	//the forward_list contains the list of leaf nodes of this tree
	std::forward_list<LeafNode*> m_liLeafNodes;
};

