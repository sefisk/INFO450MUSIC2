#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class node
{
	char artist[50];
	char song[50];
	node *next;
public:
	void setnode(char a[], char s[]);
	void display();
	friend class linkedList;
};
void node::setnode(char a[], char s[])
{
	strcpy_s(artist, a);
	strcpy_s(song, s);
	next = NULL;
}
void node::display()
{
	cout << song << " by " << artist << endl;
}


class linkedList
{
	node *head;
	node *tail;
public:
	linkedList();
	void addNodeToEnd(node *nptr);
	void skipsong(int n);
	void playsong();
	int removeNode(char e[]);
	void songInfo();
};


linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}
void linkedList::addNodeToEnd(node *ptr)
{
	
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void ClearMe() {
	cin.clear();
	cin.ignore();
}
int linkedList::removeNode(char e[])
{
	
	node *ptr = head;
	if (ptr == NULL)  
		return -1;


	if (strcmp(head->song, e) == 0)
	{
		
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}


	while (ptr != NULL)
	{
		if (ptr->next && (strcmp((ptr->next)->song, e) == 0))
		{
			
			if (tail == ptr->next)
				tail = ptr;
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}
void linkedList::skipsong(int n)
{
	
	node *ptr;
	ptr = head;
	for (int i = 0; i < n; i++)
	{
		ptr = ptr->next;
	}
}
void linkedList::playsong()
{
	node *ptr;
	ptr = head;
	if (ptr == NULL)
	{
		cout << "No song to play" << endl;
		return;
	}
	else
	{
		cout << "Now Playing: " << ptr->song << " by " << ptr->artist << endl;
		cout << endl;
	}
}
void linkedList::songInfo()
{
	node *ptr;
	ptr = head;
	while (1 == 1)
	{
		char ans;
		
		cout << "do what" << endl;
		cout << "[p]lay" << endl;
		cout << "[s]kip" << endl;
		cout << "[d]elete" << endl;
		cout << "[q]uit" << endl;
		cin >> ans;
		switch (ans)
		{
		case 'p':
		{

			if (ptr == NULL)
				ptr = head;
			cout << "playing " << ptr->artist << ", " << ptr->song << endl;
			cout << endl;
			ptr = ptr->next;
			continue;
		}
		case 's':
		{

			int i = 0;
			int num;
			cout << "How many songs to skip?" << endl;
			cin >> num;
			
			for (i; i < num; i++)
			{
				if (ptr == NULL)
					ptr = head;
				ptr = ptr->next;
			}
			continue;
		}
		case 'd':
		{
			char e[50];
			cout << "Enter Song to delete (CaSe SenSitiVE): " << endl;
			ClearMe();
			cin.getline(e, 50);
			removeNode(e);
			continue;
		}
		case 'q':
		{
			break;
		}
		}
	}
}

int main()
{
	linkedList *mylist = new linkedList();
	char s[50];
	cout << "Enter file location: " << endl;
	cin.getline(s, 50);
	ifstream infile(s);
	if (!infile)
	{
		cout << "ERROR: File not found!" << endl;
		return -1;
	}
	while (!infile.eof())
	{
		
		char a[50];
		char s[50];

		infile.getline(a, 50, ',');
		if (strlen(a))
		{
			infile.getline(s, 50, ',');
			node *p = new node();
			p->setnode(a, s);
			mylist->addNodeToEnd(p);
		}
	}
	infile.close();
	mylist->songInfo();
	return 0;
}

