
#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "InventoryManager.h"
#include <stack>
#include <iostream>

using namespace std;

void displayMenuOptions();
void runMenu(HashTable<string, Card*>* &hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, stack<Card*>* deleteStack);
void welcome();
void displayMenuOptions();
void addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* &hashTable);
void upper(string &s);
void searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable);
void deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack);
void pushOnStack(Card *TempCard, stack<Card*>* deleteStack);
void saveManager(BinarySearchTree* keyTree, stack<Card*>* deleteStack);
void DeleteStack(stack<Card*>* deleteStack);
void displayHashStats(HashTable<string, Card*>* hashTable);
void displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
void displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
void displayHashedTable(HashTable<string, Card*>* hashTable);
bool validKey(string &key);
void displayList(LinkedList &anItem);
void farewell();

int main(){

	HashTable<string, Card*>* hashTable = 0;
	BinarySearchTree* keyTree = new BinarySearchTree;
	AVLTree* nameTree = new AVLTree;
	stack<Card*>* deleteStack = new stack<Card*>;


	welcome();

	InventoryManager::inventoryCreation(keyTree, nameTree, hashTable);		//InvManager - by Jordan

	runMenu(hashTable, keyTree, nameTree, deleteStack);

	farewell();

	//Destroy Structures - by Jordan

	//InventoryManager::destroyEverything(keyTree, nameTree, hashTable);

	return 0;
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��)
//  Displays the information of all commands available to the user.
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��)
void displayMenuOptions()
{
	cout << endl;
	cout << "<A>\tAdd a card.\n\n";
	cout << "<D>\tDelete a card.\n\n";
	cout << "<F>\tSearch for a card.\n\n";
	cout << "<H>\tPrint in Hash Table Sequence.\n\n";
	cout << "<S>\tPrint Sorted List.\n\n";
	cout << "<I>\tPrint Indented Tree.\n\n";
	cout << "<V>\tSave the database.\n\n";
	cout << "<T>\tShow hash table statistics.\n\n";
	cout << "<M>\tShow Menu.\n\n";
	cout << "<Q>\tQuit.\n\n";
}

// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��)
//  Basic Menu - gets user input and switches between options.
//  Continues until user decides to quit.
// (�`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��`'�.�//(*_*)\\�.�'��)
void runMenu(HashTable<string, Card*>* &hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, stack<Card*>* deleteStack)
{
	string choice;
	do{										//cycles through commands until the user decides to quit
		cout << "Please enter a command.\t<M> for help." << endl;
		getline(cin, choice);

		switch (toupper(choice[0])){
		case 'A':
			addManager(keyTree, nameTree, hashTable);
			break;
		case 'D':
			deleteManager(keyTree, nameTree, hashTable, deleteStack);
			break;
		case 'F':
			searchManager(keyTree, nameTree, hashTable);
			break;
		case 'H':
			displayHashedTable(hashTable);
			break;
		case 'S':
			displayTreeManager(keyTree, nameTree);
			break;
		case 'I':
			displayIndentedTreeManager(keyTree, nameTree);
			break;
		case 'V':
			saveManager(keyTree, deleteStack);
			break;
		case 'T':
			displayHashStats(hashTable);
			break;
		case 'M':
			displayMenuOptions();
			break;
		case 'Q':
			// Save Manager 
			cout << "Save the database and quitting - Coming Soon!\n";
			break;
		default:
			cout << "\nCommand not understood.  Please try again!\n\n";
			break;
		}
	} while (toupper(choice[0]) != 'Q');
}

///////////////////////////////////////////////////////////////////////////////

void addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* &hashTable) {
	string key = "", buffer = "";

	cout << "ADD MANAGER\n\tPlease enter a valid serial number in the format AA111." << endl;

	if (validKey(key)) {
		Card *TempCard = new Card;

		TempCard->setCode(key);

		cout << "Enter name: ";
		getline(cin, buffer);
		upper(buffer);
		TempCard->setName(buffer);

		cout << "Enter cost: ";
		getline(cin, buffer);
		upper(buffer);
		TempCard->setCost(buffer);

		cout << "Enter rarity: ";
		getline(cin, buffer);
		upper(buffer);
		TempCard->setRarity(buffer);

		keyTree->insert(TempCard);
		cout << "Inserting into keyTree..." << endl;
		nameTree->insert(TempCard);
		cout << "Inserting into nameTree..." << endl;
		hashTable->addEntry(TempCard->getCode(), TempCard);
		cout << "Inserting into hashTable..." << endl;

		InventoryManager::checkLoadFactor(hashTable);
	}
}

void upper(string &s) {
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
}

void searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable) {
	char option = NULL, keySelection = NULL;
	string buffer;

	cout << "SEARCH MANAGER\n\t1: Key\n\t2: Name\n\n";

	cin >> option;

	if (!cin.good()) {
		cout << "Invalid input." << endl;
		return;
	}

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (option == '1') {
		if (validKey(buffer)) {
			Card *TempCard = new Card;
			if (hashTable->search(buffer, TempCard))
				cout << buffer << " found!" << *TempCard << endl;
			else
				cout << buffer << " not found." << endl;
		}
	}
	else if (option == '2') {
		cout << "Enter the name of the card: ";
		getline(cin, buffer);
		upper(buffer);
		Card *target = new Card;
		Card *TempCard = new Card;
		target->setName(buffer);
		LinkedList *listChoice = nameTree->getEntry(*target);

		while (listChoice->GetNext(TempCard))
			cout << TempCard << endl;
	}
	else
		cout << "Invalid input." << endl;
}

void deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack) {
	char option = NULL;
	string key = "", name = "";

	cout << "DELETE MANAGER\n\t1: Key\n\t2: Name\n\n";

	cin >> option;

	if (!cin.good()) {
		cout << "Invalid input." << endl;
		return;
	}

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (option == '1') {
		if (!validKey(key))
			return;
	}
	else if (option == '2') {
		cout << "Enter the name of the card to be deleted: ";
		getline(cin, name);
		upper(name);
		Card *target = new Card;
		Card *TempCard = new Card;
		target->setName(name);
		LinkedList *listChoice = nameTree->getEntry(*target);

		while (listChoice->GetNext(TempCard))
			cout << TempCard << endl;

		cout << "Enter the key of one the cards displayed above: ";
		if (!validKey(key))
			return;
	}
	else {
		cout << "Invalid input." << endl;
		return;
	}

	Card *TempCard = keyTree->findNode(key)->getCardPtr();
	pushOnStack(TempCard, deleteStack);
	cout << "Pushing " << key << " onto undo-delete stack..." << endl;

	if (keyTree->remove(key))
		cout << key << " removed from keyTree." << endl;
	else
		cout << key << " does not exist in keyTree." << endl;

	if (nameTree->remove(*TempCard))
		cout << key << " removed from nameTree." << endl;
	else
		cout << key << " does not exist in nameTree." << endl;

	if (hashTable->remove(key, TempCard))
		cout << key << " removed from hashTable." << endl;
	else
		cout << key << " does not exist in hashTable." << endl;
}

void pushOnStack(Card *TempCard, stack<Card*>* deleteStack) {
	deleteStack->push(TempCard);
}

void saveManager(BinarySearchTree* keyTree, stack<Card*>* deleteStack) {
	DeleteStack(deleteStack);
	cout << "Deleting stack..." << endl;
	InventoryManager::saveCurrentCollection(keyTree);
	cout << "Saving current collection..." << endl;
}

void DeleteStack(stack<Card*>* deleteStack) {
	while (!deleteStack->empty())
		deleteStack->pop();
}

void displayHashStats(HashTable<string, Card*>* hashTable) {
	hashTable->displayStatistics();
}

void welcome() {
	cout << "Welcome" << endl;
}

void farewell() {
	cout << "Goodbye." << endl;
}

bool validKey(string &key) {
	cout << "Enter key: ";
	getline(cin, key);

	if (key.length() != 5) {
		cout << "Invalid input." << endl;
		return false;
	}

	key[0] = toupper(key[0]);
	key[1] = toupper(key[1]);

	// 65 - 90 = A-Z
	// 48 - 57 = 0-9

	for (int i = 0; i < 2; i++) {
		if (key[i] < 65 || key[i] > 90) {
			cout << "Invalid input." << endl;
			return false;
		}
	}
	for (int i = 2; i < 5; i++) {
		if (key[i] < 48 || key[i] > 57) {
			cout << "Invalid input." << endl;
			return false;
		}
	}
	return true;
}

void displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
	char option = NULL;

	cout << "Which tree would you like to display?\n"
		<< "1: BST\n"
		<< "2: BST (Non-Unique)\n" << endl;

	cin >> option;
	while (!cin.good())
		return;

	if (option == '1') {
		if (keyTree->isEmpty())
			cout << "BST is empty! Nothing to display." << endl;
		else
			keyTree->displayTree();
	}
	else if (option == '2') {
		if (nameTree->isEmpty())
			cout << "BST (Non-Unique) is empty! Nothing to display." << endl;
		else
			nameTree->inOrder(displayList);
	}
	else
		cout << "Invalid input." << endl;

	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

void displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
	char option = NULL;

	cout << "Which tree would you like to display?\n"
		<< "1: Indented BST\n"
		<< "2: Indented BST (Non-Unique)\n" << endl;

	cin >> option;
	while (!cin.good())
		return;

	if (option == '1') {
		if (keyTree->isEmpty())
			cout << "BST is empty! Nothing to display." << endl;
		else
			keyTree->displayIndentedTree();
	}
	else if (option == '2') {
		if (nameTree->isEmpty())
			cout << "BST (Non-Unique) is empty! Nothing to display." << endl;
		else
			nameTree->indentedList(displayList);
	}
	else
		cout << "Invalid input" << endl;

	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

void displayHashedTable(HashTable<string, Card*>* hashTable) {
	if (hashTable->getListCount() == 0) {
		cout << "Hashed table is empty! Nothing to display." << endl;
		return;
	}

	char option = NULL;
	cout << "HASHED TABLE DISPLAY MANAGER\n\t1: Full Table\n\t2: Contents Only\n\n" << endl;
	cin >> option;

	if (!cin.good()) {
		cout << "Invalid input." << endl;
		return;
	}

	if (option == '1')
		hashTable->printTable(Card::display);
	else if (option == '2')
		hashTable->displayTable(Card::display);
	else
		cout << "Invalid entry." << endl;

	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

void displayList(LinkedList &anItem) {
	anItem.ResetCurr();
	Card* toPrint = 0;
	anItem.GetNext(toPrint);

	cout << "Displaying item - " << toPrint->getName();
	cout << " " << toPrint->getCode();
	while (anItem.GetNext(toPrint))
	{
		cout << ", " << toPrint->getCode();
	}
	cout << endl;
}