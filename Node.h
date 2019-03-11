#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <deque>

class Tree;
class Node
{
	public:
	Node();
	virtual ~Node();

	public:
	virtual void Print() = 0;     

	public:
	static Tree *treeCur;
};

