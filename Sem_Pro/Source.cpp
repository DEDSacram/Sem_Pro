#include <iostream>
#include <Windows.h>
#include <stdexcept>
#include <fstream>
#include "resource.h"

#include <typeinfo>
#include <vector>

#include <cassert>

#include <regex>



HMODULE GTX() {
	HMODULE module = NULL;
	GetModuleHandleEx(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		(LPCTSTR)GTX,
		&module);
	return module;
}
//# * id .......... identifikační číslo osoby
//# * givenName ... jméno
//# * sn .......... příjmení
//# * birthday .... datum narození YYYY-m-d
//# * height ...... výška
//# * weight ...... váha
//# * mother_id ... identifikační číslo matky (-1 = nedefinované)
//# * father_id ... identifikační číslo otce (-1 = nedefinované)
class Person {
public:
	int id;
	std::string givenName;
	std::string sn;
	std::string birthday;
	int height;
    double weight;
	int mother_id;
	int father_id;
	Person(double p_weight,int p_id,int p_father_id, std::string p_birthday, std::string p_sn, int p_height, std::string p_givenName, int p_mother_id) {
		id = p_id;
		givenName = p_givenName;
		sn = p_sn;
		birthday = p_birthday;
		height = p_height;
		weight = p_weight;
		mother_id = p_mother_id;
		father_id = p_father_id;
	}
};

std::vector<std::string> split_return(std::string str, char del) {
	std::string temp = "";
	std::vector<std::string> string_split;
	int size = (int)str.size();
	for (int i = 0; i < size; i++) {
		if (str[i] == del) {
			string_split.push_back(temp);
			temp = "";
		}
		else {
			temp += str[i];
		}
	}
	string_split.push_back(temp);
	return string_split;
}




struct Node {
	int data;
	struct Node* prev, * next;
};

Node* newNode(int val)
{
	Node* temp = new Node;
	temp->data = val;
	temp->prev = temp->next = nullptr;
	return temp;
}
void displayList(Node* head)
{
	while (head->next != nullptr) {
		std::cout << head->data << " <==> ";
		head = head->next;
	}
	std::cout << head->data << std::endl;
}

// Insert a new node at the head of the list
void insert(Node** head, int node_data)
{
	Node* temp = newNode(node_data);
	temp->next = *head;
	(*head)->prev = temp;
	(*head) = temp;
}

// reverse the doubly linked list
void reverseList(Node** head)
{
	Node* left = *head, * right = *head;

	// traverse entire list and set right next to right
	while (right->next != nullptr)
		right = right->next;

	//swap left and right data by moving them towards each other till they meet or cross
	while (left != right && left->prev != right) {

		// Swap left and right pointer data
	/*	swap(left->data, right->data);*/
		
		int temp = left->data;
		left->data = right->data;
		right->data = temp;

		// Advance left pointer
		left = left->next;

		// Advance right pointer
		right = right->prev;
	}
}




//struct node {
//	// part which will store data
//	Person data;
//	// pointer to the previous node
//	node* prev;
//	// pointer to the next node
//	node* next;
//
//};
//
//struct  doubly_linked_list_t {
//	node* head;
//	node* tail;
//};
//
//// function to revrese the doubly linked list
//void reverse(node** head_ref)
//{
//	node* temp = NULL;
//	node* current = *head_ref;
//
//	// to reverse the list we just swap the next and prev of all the nodes
//	while (current != NULL) {
//		temp = current->prev;
//		current->prev = current->next;
//		current->next = temp;
//		current = current->prev;
//	}
//
//	// edge case
//	if (temp != NULL)
//		*head_ref = temp->prev;
//}

//typeid(result).name()
int main() {

	Node* headNode = newNode(5);
	insert(&headNode, 4);
	insert(&headNode, 3);
	insert(&headNode, 2);
	insert(&headNode, 1);
	std::cout << "Original doubly linked list: " << std::endl;
	displayList(headNode);
	std::cout << "Reverse doubly linked list: " << std::endl;
	reverseList(&headNode);
	displayList(headNode);









































	std::string result;
	HRSRC res = FindResource(GTX(), MAKEINTRESOURCE(PEOPLE_TEXT), MAKEINTRESOURCE(TEXTFILE));
	if (res == 0) throw std::invalid_argument("File not found");
	
	HGLOBAL data = LoadResource(GTX(), res);
	DWORD size = SizeofResource(GTX(), res);
	char* final = (char*)LockResource(data);
	result.assign(final, size);

	//storing to vbs
	//doubly_linked_list_t list = { NULL, NULL };
	//doubly_linked_list_t* lst = &list;
	
	std::vector<std::string> person_info = split_return(result, '\n');
	/*std::regex rx("(^[1-9](?:[0-9]*)?[\\.][0-9]),([0-9]{5}),((?:-1|[0-9]{5})),([0-9]*[-][0-9]{1,2}[-][0-9]{1,2}),([A-Z][a-z]*),([0-9]{1,3}),([A-Z][a-z]*),((?:-1|[0-9]{5}))");*/
	std::regex rx("^([1-9][0-9]?\.[0-9]),([1-9][0-9]{4}),(-1|[1-9][0-9]{4}),([1-9][0-9]{3}-(?:[1-9]|1[0-2])-(?:[1-9]|[1-3][0-9])),([A-Z][a-z]*),([1-9][0-9]{0,2}),([A-Z][a-z]*),(-1|[1-9][0-9]{4})");

	for (std::string i : person_info) {
		
		std::match_results< std::string::const_iterator > mr;
		std::regex_search(i, mr, rx);

		if (mr.size() - 1 != 8) {
			throw std::invalid_argument("Validation error occured");
		}
		//double p_weight, int p_id, int p_father_id, std::string p_birthday, std::string p_sn, int p_height, std::string p_givenName, int p_mother_id
		Person record = Person((double)stod(mr[1].str()), stoi(mr[2].str()), stoi(mr[3].str()), mr[4].str(), mr[5].str(), stoi(mr[6].str()), mr[7].str(), stoi(mr[6].str()));
		/*push_dll(record, lst);*/
		/*allocate_dll_entry(record);*/
	}


	//std::cout << typeid(lst->head->value).name();




	/*print_dll(lst->head->value.id);*/
	//printf("Revert print: ");
	//printReverse(lst);
	//free_dll(lst);

	return 0;
}