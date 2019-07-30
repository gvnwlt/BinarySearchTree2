//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : JYour name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm> // had to include because this is where "remove" lives

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// FIXME (1): Internal structure for tree node
struct Node {
	Bid nbid;
	struct Node* left;
	struct Node* right;
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    Node* cur;
    Node* par;
    Node* pre;
    Node* suc;
    Node* temp;
    bool loaded;
    int dropList[1000];

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);
    //Node* current;

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
	root = NULL;
	cur = NULL;
	par = NULL;
	pre = NULL;
	suc = NULL;
	temp = NULL;
	loaded = true;
	dropList[1000] = {};

}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
	if (root->left == NULL && root->right == NULL) {
		free(root);
	}
	delete(root->left);
	delete(root->right);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
	if (!loaded) {
		cout << "A tree has not been loaded yet..." << endl;
	}
	else {
		cout << "now passing root to inorder" << endl;
		inOrder(root);
	}
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) Implement inserting a bid into the tree
	Node* node = new Node();
	addNode(node, bid);
	//cout << "another one" << endl;
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (4a) Implement removing a bid from the tree
	cur = root;
	par = NULL; // reset to NULL

	while (cur != NULL) {
		if (cur->nbid.bidId == bidId) { // the current node is identified as a match
			if (!cur->left && !cur->right) { // no children
				if (!par) {
					root == NULL;
				}
				else if (par->left == cur) { // if this is left child
					par->left == NULL;
				}
				else {						// if this is right child
					par->right == NULL;
				}
			}
			else if (cur->left && !cur->right) { // has left child
				if (!par) {
					root = cur->left;
				}
				else if (par->left == cur) {
					par->left = cur->left;
				}
				else {
					par->right = cur->left;
				}
			}
			else if (!cur->left && cur->right) { // has right child
				if (!par) {
					root = cur->right;
				}
				else if (par->left == cur) {
					par->left = cur->right;
				}
				else {
					par->right = cur->right;
				}
			}
			else {
				cout << "current children " << cur->left->nbid.bidId << " and " << cur->right->nbid.bidId << endl;
				temp = cur; // use as temporary store of current so that the left and right can be set after the swap to successor
				if (par->left == cur) {
					cout << "on the left!" << endl;
					suc = cur->right;
					while (suc->left != NULL) {
						pre = suc;
						suc = suc->left;
					}
					cur = suc; // copy successor to current node

					cur->left = temp->left; // set current node left and right to the previous
					cur->right = temp->right;
					pre->left = NULL;	// take the node just before the successor and change its left to NULL
					cout << "doing swap thingy if two children found on node to be removed..." << endl;
					cout << "found successor " << cur->nbid.bidId << " and now has children " << cur->left->nbid.bidId << " and " << cur->right->nbid.bidId << endl;
					par->left = cur;
					break;
				}
				else {
					cout << "on the right!" << endl;
					suc = cur->right;
					while (suc->left != NULL) {
						pre = suc;
						suc = suc->left;
					}
					cur = suc; // copy successor to current node

					cur->left = temp->left; // set current node left and right to the previous
					cur->right = temp->right;
					pre->left = NULL;	// take the node just before the successor and change its left to NULL
					cout << "doing swap thingy if two children found on node to be removed..." << endl;
					cout << "found successor " << cur->nbid.bidId << " and now has children " << cur->left->nbid.bidId << " and " << cur->right->nbid.bidId << endl;
					par->right = cur;
					break;
				}
			}
			cout << "found " << cur->nbid.bidId << " with children " << cur->left->nbid.bidId << " and " << cur->right->nbid.bidId << endl;
			break;
		}
		else if (cur->nbid.bidId < bidId) {
			par = cur;
			cur = cur->right;
			cout << "searching to delete going right" << endl;
		}
		else {
			par = cur;
			cur = cur->left;
			cout << "searching to delete going left" << endl;
		}

		if (cur != NULL) {
			cout << "now on " << cur->nbid.bidId << endl;
		}

	}
	cout << "removal process complete" << endl;
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (3) Implement searching the tree for a bid
	cur = root;
	Bid bid;

	while (cur != NULL) {
		if (cur->nbid.bidId == bidId) { // if the current has the key then done on each iteration
			return cur->nbid;
		}
		else if (bidId < cur->nbid.bidId) { // keep searching through the tree based on if the value is less/greater than current
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (2b) Implement inserting a bid into the tree
	if (root == NULL) { // root node gets established if not there already
		root = node;
		root->nbid = bid;
		cout << "first node added " << root->nbid.title << endl;
	}
	else {
		cur = root;
		while (cur != NULL) {
			if (bid.bidId < cur->nbid.bidId) { // if the key is less than root key go left
				if (cur->left == NULL) { // if no left node have node take the spot now and exit the loop
					cur->left = node;
					cur->left->nbid = bid;
					cout << "added left "<< cur->left->nbid.title << endl;
					break;
				}
				else {
					cur = cur->left; // move down to left node to continue checks
					//cout << "moving left" << endl;
				}
			}
			else {
				if (cur->right == NULL) { // if no right node have node take the spot now and exit the loop
					cur->right = node;
					cur->right->nbid = bid;
					cout << "added right " << cur->right->nbid.title << endl;
					break;
				}
				else {
					cur = cur->right; // move down to right node to continue checks
					//cout << "moving right" << endl;
				}
			}
		}
	}
}

void BinarySearchTree::inOrder(Node* node) {
	if (node == NULL) {
		return;
	}
	//cout << "displaying bids now" << endl;

	inOrder(node->left);
	cout << node->nbid.bidId << " | " << node->nbid.title << " | " << node->nbid.fund << endl;
	inOrder(node->right);

}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "src/eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

       // bst = new BinarySearchTree(); // moved out of case 1 because why have it there?

        switch (choice) {

        case 1:
        	bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
