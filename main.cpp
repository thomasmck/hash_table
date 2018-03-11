/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Tom
 *
 * Created on 08 March 2018, 20:25
 */

#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// Code originally from: http://www.sparknotes.com/cs/searching/hashtables/section1/
int hash_generator(char *str, int table_size)
{
	int sum;

	/* Make sure a valid string passed in */
	if (str==NULL) return -1;

	/* Sum up all the characters in the string */
	for( ; *str; str++){ 
            sum += *str;
            // Pointer changes if we don't print?
            // Complicated reason for this: https://stackoverflow.com/questions/32924282/why-does-the-print-statement-change-the-value-of-pointer
            cout<<sum<<", "<<*str<<" ,";
        }
        cout<<endl;

	/* Return the sum mod the table size */
	return sum % table_size;
}

//Code originally from: https://gist.github.com/charlierm/5691020
class Node
{
public:
    Node* next;
    char data;
};

using namespace std;

class LinkedList
{
public:
    int length;
    Node* head;

    LinkedList();
    ~LinkedList();
    void add(char data);
    void print();
    bool search(char data);
};

LinkedList::LinkedList(){
    this->length = 0;
    this->head = NULL;
}

LinkedList::~LinkedList(){
    std::cout << "LIST DELETED"<<endl;
}

void LinkedList::add(char data){
    Node* node = new Node();
    node->data = data;
    node->next = this->head;
    this->head = node;
    this->length++;
}

void LinkedList::print(){
    Node* head = this->head;
    int i = 1;
    while(head){
        std::cout << i << ": " << head->data << std::endl;
        head = head->next;
        i++;
    }
}

bool LinkedList::search(char data){
    Node* head = this->head;
    while(head){
        if (head->data == data) return true;
        head = head->next;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    // List of stuff to add to hash_table
    char stuffs[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    
    // Need to create all lists separately as they are pointers
    int hash_table_size = 4;
    LinkedList* list1 = new LinkedList();
    LinkedList* list2 = new LinkedList();
    LinkedList* list3 = new LinkedList();
    LinkedList* list4 = new LinkedList();
    LinkedList* hash_table[] = {list1, list2, list3, list4};
    
    // Loop through stuffs and populate hash_table
    cout<<"Populating Hash Table"<<endl;
    for(char &stuff : stuffs)
    {
        // Pointer to char
        char *char_pointer = &stuff;
        
        // Generate hash number
        int hash_num = hash_generator(char_pointer, hash_table_size);

        // Add the char to the correct place in the hash_table
        // Pointer changes if we don't print?
        cout<<"STUFF: "<<stuff<<", HASH_NUM: "<<hash_num<<", POINTER: "<<char_pointer<<endl;
        hash_table[hash_num]->add(stuff);
    }
    
    // Loop through hash_table and print contents
    cout<<"Printing hash table contents"<<endl;
    for(LinkedList* &linked_list : hash_table){
        linked_list->print();
        cout << "List Length: " << linked_list->length <<endl;
    }
    
    // Searching hash table for a value
    cout<<"Searching Hash Table"<<endl;
    
    char search_value = stuffs[3];
    char *search_pointer = &stuffs[3];
    int hash_num = hash_generator(search_pointer, hash_table_size);
    
    bool exists = hash_table[hash_num]->search(search_value);
    cout<<"Exists = "<<exists<<endl;
    
    return 0;
}

