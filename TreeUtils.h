#pragma once

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include "Node.h"
#include <vector>
#include <functional>

using comparatorType = std::function<bool(const std::pair<int, int>&, const std::pair<int, int>&)>;

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

	virtual void AddVertex(int data, int bal = 0, int wgh = 0);
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

	void AddVertex(int data, int bal = 0, int wgh = 0) override;
	bool DeleteVertex(int key) override;
};

class BBT : public BinaryTree {
private:
	int _vr = 1, _hr = 1;

public:
	BBT();

	void AddVertex(int data, int bal = 0, int wgh = 0) override;
	int GetLevels() const;
};

class OST : public BinaryTree {
protected:
	std::vector<std::vector<int>> _weights, _heights, _roots;

	void CalculateWeights(const std::vector<std::pair<int, int>>& keysWithWeights);
	void CalculateHeightsRoots(int n);

public:
	OST();

	const std::vector<std::vector<int>>& GetWeights() const;
	const std::vector<std::vector<int>>& GetHeights() const;
	const std::vector<std::vector<int>>& GetRoots() const;
	
	double GetWeightedAvgHeight() const;
	double GetRatioHeightsWeights() const;

	virtual void Create(std::vector<std::pair<int, int>>& keysWithWeights);
};

class A1 : public OST {
protected:
	void QuickSortPairs(std::vector<std::pair<int, int>>& keysWithWeights, comparatorType comp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
		return (a.second > b.second) || (a.second == b.second && a.first < b.first);
	});

public:
	A1();

	void Create(std::vector<std::pair<int, int>>& keysWithWeights) override;
};

class A2 : public A1 {
public:
	A2();

	void Create(std::vector<std::pair<int, int>>& keysWithWeights) override;
};

class CodeTree : public BinaryTree {
public:
	CodeTree();

	void AddVertex(char symbol, const int* code, size_t size);
};

Vertex* CreateVertex(int value, int balance = 0, int weight = 0);

#endif // !TREE_UTILS_H