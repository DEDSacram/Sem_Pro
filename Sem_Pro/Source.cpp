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


class Person {        // The class
public:          // Access specifier
	int id;  // Attribute
	std::string givenName;  // Attribute
	std::string sn;
	std::string birthday;
	int height;
    double weight;
	int mother_id;
	int father_id;
	// int p_id,std::string p_givenName, std::string p_sn, std::string p_birthday, int p_height, int p_weight, int p_mother_id, int p_father_id
	//Person(int p_weight,int p_id,int p_father_id, std::string p_birthday, std::string p_sn, int p_height, std::string p_givenName, int p_mother_id)
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


//linked
typedef struct dll_entry {
	int value;
	struct dll_entry* prev;
	struct dll_entry* next;
} dll_entry_t;
typedef struct {
	dll_entry_t* head;
	dll_entry_t* tail;
} doubly_linked_list_t;

dll_entry_t*
allocate_dll_entry(int
	value)
{
	dll_entry_t* new_entry = (
		dll_entry_t*)malloc(
			sizeof(dll_entry_t));
	assert(new_entry);
	new_entry->value = value;
	new_entry->next = NULL;
	new_entry->prev = NULL;
	return new_entry;
}

void insert_dll(int value, dll_entry_t* cur)
{
	assert(cur);
	dll_entry_t* new_entry = allocate_dll_entry(value);
	new_entry->next = cur;
	new_entry->prev = cur->prev;
	if (cur->prev != NULL) {
		cur->prev->next = new_entry;
	}
	cur->prev = new_entry;
}

void push_dll(int value, doubly_linked_list_t* list)
{
	assert(list);
	dll_entry_t* new_entry = allocate_dll_entry(value);
	if (list->head) { // an entry already in the list
		new_entry->next = list->head; // connect new -> head
		list->head->prev = new_entry; // connect new <- head
	}
	else { //list is empty
		list->tail = new_entry;
	}
	list->head = new_entry; //update the head
}

void print_dll(const doubly_linked_list_t* list)
{
	if (list && list->head) {
		dll_entry_t* cur = list->head;
		while (cur) {
			printf("%i%s", cur->value, cur->next ? " " : "\n");
			cur = cur->next;
		}
	}
}
void printReverse(const doubly_linked_list_t* list)
{
	if (list && list->tail) {
		dll_entry_t* cur = list->tail;
		while (cur) {
			printf("%i%s", cur->value, cur->prev ? " " : "\n");
			cur = cur->prev;
		}
	}
}

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


//typeid(result).name()
int main() {
	std::string result;
	HRSRC res = FindResource(GTX(), MAKEINTRESOURCE(PEOPLE_TEXT), MAKEINTRESOURCE(TEXTFILE));
	if (res == 0) throw std::invalid_argument("File not found");
	
	HGLOBAL data = LoadResource(GTX(), res);
	DWORD size = SizeofResource(GTX(), res);
	char* final = (char*)LockResource(data);
	result.assign(final, size);

	doubly_linked_list_t list = { NULL, NULL };
	doubly_linked_list_t* lst = &list;
	
	std::vector<std::string> person_info = split_return(result, '\n');
	/*std::regex rx("(^[1-9](?:[0-9]*)?[\\.][0-9]),([0-9]{5}),((?:-1|[0-9]{5})),([0-9]*[-][0-9]{1,2}[-][0-9]{1,2}),([A-Z][a-z]*),([0-9]{1,3}),([A-Z][a-z]*),((?:-1|[0-9]{5}))");*/
	std::regex rx("^([1-9][0-9]?\.[0-9]),([1-9][0-9]{4}),(-1|[1-9][0-9]{4}),([1-9][0-9]{3}-(?:[1-9]|1[0-2])-(?:[1-9]|[1-3][0-9])),([A-Z][a-z]*),([1-9][0-9]{0,2}),([A-Z][a-z]*),(-1|[1-9][0-9]{4})");

	for (std::string i : person_info) {
		
		std::match_results< std::string::const_iterator > mr;
		std::regex_search(i, mr, rx);

		if (mr.size() - 1 != 8) {
			throw std::invalid_argument("Validation error occured");
		}
		//std::stoi()
		std::cout << mr[0];
		std::cout << std::endl;

		//double p_weight, int p_id, int p_father_id, std::string p_birthday, std::string p_sn, int p_height, std::string p_givenName, int p_mother_id
		Person ent5 = Person((double)stod(mr[1].str()),stoi(mr[2].str()), stoi(mr[3].str()),mr[4].str(), mr[5].str(), stoi(mr[6].str()),mr[7].str(), stoi(mr[6].str()));
	}

	/*, mr[2], mr[3], mr[4], mr[5], mr[6], mr[7], mr[8]*/

	
	

	//printf("Regular print: ");
	//print_dll(lst);
	//printf("Revert print: ");
	//printReverse(lst);
	//free_dll(lst);

	return 0;
}