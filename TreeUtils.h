#pragma once

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include "Node.h"

class BinaryTree {
public:
	Vertex* root;

	BinaryTree();
	~BinaryTree();

	void PrintRootLeftRight();
	void PrintLeftRootRight();
	void PrintLeftRightRoot();
	void PrintInfo();

	int GetSize();
	int GetSum();
	int GetHeight();
	double GetAvgHeight();
	void CalculateSumOfPath(int currentHeight, int& totalHeight);

	Vertex* FindVertex(int key);

	virtual void AddVertex(int data);
	virtual bool DeleteVertex(int key);

	void Delete();
};

class PBST : public BinaryTree {
public:
	PBST();

	void Create(int* arr, int size);
};

class RST : public BinaryTree {
public:
	RST();

	void AddVertexDoubleIndirection(int data);
};

class AVL : public BinaryTree {
private:
	bool _decrease = false;
	bool _grow = true;

protected:
	void RotateLL(Vertex*& p);
	void RotateRR(Vertex*& p);
	void RotateLR(Vertex*& p);
	void RotateRL(Vertex*& p);
	void RotateLL1(Vertex*& p);
	void RotateRR1(Vertex*& p);
	void DeleteT2(Vertex*& p, Vertex*& q);
	void BalanceLeftDelete(Vertex*& p);
	void BalanceRightDelete(Vertex*& p);

public:
	AVL();

	void AddVertex(int data) override;
	bool DeleteVertex(int key) override;
};

class BBT : public BinaryTree {
private:
	int vr = 1, hr = 1;

public:
	BBT();

	void AddVertex(int data) override;
	int GetLevels() const;
};

Vertex* CreateVertex(int value);

#endif // !TREE_UTILS_H