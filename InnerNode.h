#pragma once
#include "Node.h"
class InnerNode :
	public Node
{
	public:
	InnerNode();
	virtual ~InnerNode();

	public:
	void Print() override;

	public:
	size_t GetCNodes();
	void SetCNodes(size_t);
	
	Node* GetChldNode(size_t);    //get the child node pointer in given position

	void InsertNode(Node*, int ikey);     //insert a new child node

	InnerNode *GetPrecNode();
	void SetPrecNode(InnerNode*);

	private:
	size_t cnodes;    //current nodes number
	size_t cnodesMax;  //max nodes number

	int *pKey;           //pointer to the range key

	Node **m_pChldNode;    //pointer to the child node
	InnerNode *m_pprecNode;
};

