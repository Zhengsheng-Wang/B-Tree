#pragma once
#include "Node.h"
class LeafNode :
	public Node
{
	public:
	//LeafNode(InnerNode*);
	LeafNode(int*);
	LeafNode(int*, InnerNode*);
	virtual ~LeafNode();

	public:
	void Print() override;

	size_t GetCKeys();
	void SetCKeys(size_t);

	void InsertKey(int);

	InnerNode* GetPrecNode();
	void SetPrecNode(InnerNode*);
	
	private:
	size_t ckeys;  //the number of the keys 
	size_t ckeysMax;   //the max number of the keys

	int *pKey;    //the pointer pointing to the keys contained in this node

	InnerNode *m_pprecNode;
};

