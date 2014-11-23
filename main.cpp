// Team 3 Group Project 
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "InventoryManager.h"
#include <stack>
#include <iostream>

using namespace std;

void displayMenuOptions();
void runMenu(HashTable<string, Card*>* hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, stack<Card*>* deleteStack, InventoryManager& manage_inventory);
//void tempMenu();

int main(){

	HashTable<string, Card*>* hashTable = 0;
	BinarySearchTree* keyTree = new BinarySearchTree;
	AVLTree* nameTree = new AVLTree;
	stack<Card*>* deleteStack = new stack<Card*>;
	InventoryManager manage_inventory;


	//Welcome Function - by Efrain

	manage_inventory.inventoryCreation(keyTree, nameTree, hashTable);		//InvManager - by Jordan

	hashTable->printTable(Card::display);
	//runMenu(hashTable, keyTree, nameTree, deleteStack, manage_inventory);

	//Farewell Function - by Efrain

	//Destroy Structures - by Jordan

	//manage_inventory->destroyEverything(keyTree, nameTree, hashTable);

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
void runMenu(HashTable<string, Card*>* hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, stack<Card*>* deleteStack, InventoryManager& manage_inventory)
{
	string choice;
	do{										//cycles through commands until the user decides to quit
		cout << "Please enter a command.\t<M> for help." << endl;
		getline(cin, choice);

		switch (toupper(choice[0])){
		case 'A':
			//Add Manager - by Efrain
			cout << "Add a card - Coming Soon!\n";
			break;
		case 'D':
			//Delete Manager - by Efrain
			cout << "Delete a card - Coming Soon!\n";
			break;
		case 'F':
			//Search Manager - by Efrain
			cout << "Search for a card - Coming Soon!\n";
			break;
		case 'H':
			//Display Hash List - by Nick
			cout << "Print in Hash Table Sequence - Coming Soon!\n";
			break;
		case 'S':
			//Display Sorted Manager - by Efrain
			cout << "Print Sorted List - Coming Soon!\n";
			break;
		case 'I':
			//Display Indented List Manager - by Efrain
			cout << "Print Indented Trees - Coming Soon!\n";
			break;
		case 'V':
			//Save Manager - by Efrain
			cout << "Save the database - Coming Soon!\n";
			break;
		case 'T':
			//Display Hash Statistics - by Nick of Efrain??
			cout << "Show hash table statistics - Coming Soon!\n";
			break;
		case 'M':
			displayMenuOptions();
			break;
		case 'Q':
			// Save Manager and Farwell Message? 
			cout << "Save the database and quitting - Coming Soon!\n";
			break;
		default:
			cout << "\nCommand not understood.  Please try again!\n\n";
			break;
		}
	} while (toupper(choice[0]) != 'Q');
}


