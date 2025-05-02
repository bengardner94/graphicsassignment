#include "LinkedLists.h"

LinkedLists::LinkedLists()
{

}
LinkedLists::~LinkedLists()
{

}

ListNode* LinkedLists::MakeNode(ListNode** head, int d)
{
	ListNode* newNode = new ListNode;
	ListNode* last = *head;

	newNode->data = d;
	newNode->next = nullptr;

	if (*head = nullptr)
	{
		*head = newNode;
		return newNode;
	}

	while (last->next != nullptr)
	{
		last = last->next;
	}

	last->next = newNode;

	return newNode;
}
ListNode* LinkedLists::InsertFirst(ListNode** head, int d)
{
	ListNode* newNode = new ListNode;

	newNode->data = d;
	newNode->next = *head;
	*head = newNode;

	return newNode;
}
void LinkedLists::InsertAfter(ListNode* lastNode, int d)
{
	ListNode* newNode = new ListNode;
	
	newNode->data = d;
	newNode->next = lastNode->next;
	lastNode->next = newNode;
}
void LinkedLists::DeleteList(ListNode** node)
{
	ListNode* pTemp = *node;
	ListNode* next;

	while (pTemp != nullptr)
	{
		next = pTemp->next;
		delete pTemp;
		pTemp = next;
	}
	*node = nullptr;
}
void LinkedLists::DeleteAfter(ListNode* node)
{
	ListNode* pTemp;
	if (node != nullptr && node->next != nullptr)
	{
		pTemp = node->next;
		node->next = pTemp->next;

		delete pTemp;
	}
}

void LinkedLists::DeleteNode(ListNode* node, int pos)
{
	int count = 0;
	ListNode* pTemp;
	while (node != nullptr)
	{
		if (count == pos && node != nullptr && node->next != nullptr)
		{
			pTemp = node->next;
			node->next = pTemp->next;

			delete pTemp;
		}
		count++;
		node = node->next;
	}
	std::cout << pos << " was not a valid position..." << std::endl;
}

ListNode* LinkedLists::GetNode(ListNode* node, int pos)
{
	int count = 0;

	while (node != nullptr)
	{
		if (count == pos)
		{
			std::cout << "Data stored at position " << pos << " is: " << node->data << std::endl;
			return node;
		}
		count++;
		node = node->next;
	}

	std::cout << pos << " was not a valid position..." << std::endl;
	return nullptr;
}
ListNode* LinkedLists::Find(ListNode* node, int val)
{
	while (node != nullptr)
	{
		if (node->data = val)
		{
			return node;
		}
		node = node->next;
	}

	std::cout << "Could not find " << val << std::endl;
	return nullptr;
	
}
void LinkedLists::PrintList(ListNode* node)
{
	while (node != nullptr)
	{
		std::cout << std::setw(5) << "| " << node->data << " |-->";
		node = node->next;
	}

	if (node == nullptr)
	{
		std::cout << "| NULL |" << std::endl;
	}
	std::cout << std::endl;
}