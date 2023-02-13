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

	Person() {
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

class node //struct
{
public:
    //previous nad next
    node* previousptr;
    node* nextptr;

    int data;
    ////////////////////////////////just to asure that user can insert any data type value in the linked list
    Person person;
    ////////////////////////////////just to asure that user can insert any data type value in the linked list
    node()
    {
        previousptr, nextptr = NULL;
    }
    node(Person p) {
        person = p;
        previousptr ,nextptr = NULL;
    }
    ////////////////////////////////just to asure that user can insert any data type value in the linked list
    //TO Get the data
    Person getpersonData()
    {
        return person;
    }
    //TO Set the data
    void setpersonData(Person p) {
        person = p;
    }
    //////////////////////////////Just for the sake of implementing for any data type//////////////////////////////
    node* getNextptr()
    {
        return nextptr;
    }
    void setnextptr(node* nptr)
    {
        nextptr = nptr;
    }
};


class linkedlist
{
    node* tailptr;
    node* headptr;
    node* addnodeatspecificpoition;

public:
    linkedlist()
    {
        headptr = NULL;
    }
    void insertionAtTail(node* n)
    {
        if (headptr == NULL)
        {
            headptr = n;
        }
        else
        {
            node* rptr = headptr;
            while (rptr->getNextptr() != NULL)
            {
                rptr = rptr->getNextptr();
            }
            rptr->setnextptr(n);
        }
    }

    void insertionAtHead(node* n)
    {
        node* tmp = n;
        tmp->setnextptr(headptr);
        headptr = tmp;
    }

    int sizeOfLinkedList()
    {
        int i = 1;
        node* ptr = headptr;
        while (ptr->getNextptr() != NULL)
        {
            ++i;
            ptr = ptr->getNextptr();
        }
        return i;
    }

    bool isListEmpty() {
        if (sizeOfLinkedList() <= 1)
        {
            return true;
        }
        else
        {
            false;
        }
    }

    void insertionAtAnyPoint(node* n, int position)
    {
        if (position > sizeOfLinkedList() || position < 1) {
            std::cout << "\n\nInvalid insertion at index :" << position;
            std::cout << ".There is no index " << position << " in the linked list.ERROR.\n\n";
            return;
        }

        addnodeatspecificpoition = new node;
        addnodeatspecificpoition = n;
        addnodeatspecificpoition->setnextptr(NULL);



        if (headptr == NULL)
        {
            headptr = addnodeatspecificpoition;
        }
        else if (position == 0)
        {
            addnodeatspecificpoition->setnextptr(headptr);
            headptr = addnodeatspecificpoition;
        }
        else
        {
            node* current = headptr;
            int i = 1;
            for (i = 1; current != NULL; i++)
            {
                if (i == position)
                {
                    addnodeatspecificpoition->setnextptr(current->getNextptr());
                    current->setnextptr(addnodeatspecificpoition);
                    break;
                }
                current = current->getNextptr();
            }
        }
    }


    friend std::ostream& operator<<(std::ostream& output, const linkedlist& L)
    {
     
        int i = 1;
        node* ptr = L.headptr;
        while (ptr->getNextptr() != NULL)
        {
            ++i;
           
            /// <summary>
            output << ptr->getpersonData().id << std::endl;
          
            /// </summary>
            /// <param name="output"></param>
            /// <param name="L"></param>
            /// <returns></returns>

            ptr = ptr->getNextptr();
        }

        /// <summary>
      
       output << ptr->getpersonData().id << std::endl;
     
        /// </summary>
        /// <param name="output"></param>
        /// <param name="L"></param>
        /// <returns></returns>

        if (ptr->getNextptr() == NULL)
        {
            output << "\nNULL (There is no pointer left)\n";
        }
        return output;
    }
    ~linkedlist() {
        delete addnodeatspecificpoition;
    }
};



//typeid(result).name()
int main() {

	linkedlist L1;


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
        L1.insertionAtTail(new node(record));
	}
    std::cout << L1;

    std::cout << "\nThe size of linked list after insertion of elements is : " << L1.sizeOfLinkedList();

	return 0;
}