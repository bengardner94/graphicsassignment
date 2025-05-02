#pragma once
#include "Structures.h"
#include <iostream>
#include <iomanip>
class LinkedLists
{
public:
	LinkedLists();
	~LinkedLists();

	ListNode* MakeNode(ListNode** head, int d);
	ListNode* InsertFirst(ListNode** head, int d);
	void InsertAfter(ListNode* lastNode, int d);
	void DeleteList(ListNode** node);
	void DeleteAfter(ListNode* node);
	void DeleteNode(ListNode* node, int pos);
	ListNode* GetNode(ListNode* node, int pos);
	ListNode* Find(ListNode* node, int val);
	void PrintList(ListNode* node);
private:
	ListNode* head = nullptr;
};

