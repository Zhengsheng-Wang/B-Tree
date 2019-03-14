#pragma once
#include "Node.h"
class InnerNode :
	public Node
{
	friend std::ostream& operator<<(std::ostream &, const InnerNode&);

	public:
	InnerNode();
	InnerNode(int, int*, Node**);
	virtual ~InnerNode();

	public:
	Node* GetChldNode(size_t) const;    //get the child node pointer in given position
	size_t GetKey(size_t) const;

	void InsertKey(int) override;      //insert key
	void InsertChldNode(Node*, int ikey);     //insert a new child node

	size_t GetCChldNodes() const;

	InnerNode *GetPrecNode() const override;
	void SetPrecNode(InnerNode*) override;

	private:
	size_t m_cnodes;    //current nodes number
	size_t m_cnodesMax;  //max nodes number

	int *m_piKeyArr;           //pointer to the range key

	Node **m_pChldNodeArr;    //pointer to the child node array
	InnerNode *m_pprecNode;  //pointer to the prec node
};

