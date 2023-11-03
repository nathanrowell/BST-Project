#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;
// Nathan Rowell CISC220013
BST::BST() {
    root = nullptr;
	
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
    root = new BSTNode(title, author,yr,pub,isbn, rate);
	
}

BST::~BST() {
	clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
    BSTNode *newNode = new BSTNode(title,author,yr,pub,isbn,rate);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    BSTNode *current = root;
    while (current != nullptr) {
        if (*current->book > *newNode->book) {
            if (current->left == nullptr) {
                current->left = newNode;
                newNode->parent=current;
                setHeight(newNode);
                return;
            }
            else {
                current = current->left;

            }

        }
        else if (*current->book <= *newNode->book){
            if (current->right == nullptr) {
                current->right = newNode;
                newNode->parent=current;
                setHeight(newNode);
                return;
            }
            else {
                current = current->right;
            }
        }
        else {
            return;
        }
    }

	
}

BSTNode *BST::find(string title, string author) {
    return find(title,author,root);
}

BSTNode *BST::find(string title, string author, BSTNode *start) {
    BSTNode *current = start;

    while (current != nullptr) {
        if (current->book->title == title && current->book->author == author) {
            return current; }
        else if (current->book->author == author) {
            if (current->book->title < title) {
                current = current->right;
            }
            else {
                current = current->left;
            }
        }
        else {
            if (current->book->author < author) {
                current = current->right; }

            else {
                current = current->left; }
        }

    }
    return NULL;
}


void BST::printTreeIO() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing In-Order:" << endl;
		printTreeIO(root);
	}
}

void BST::printTreeIO(BSTNode *node) {
    if (node == nullptr) {
        return;
    }
    printTreeIO(node->left);
    node->printNode(false);
    printTreeIO(node->right);
	
}

void BST::printTreePre() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing Pre-Order:" << endl;
		printTreePre(root);
	}
}

void BST::printTreePre(BSTNode *node) {
    if (node == nullptr) {
        return;
    }
    node->printNode(false);
    printTreePre(node->left);
    printTreePre(node->right);
}

void BST::printTreePost() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing Post-Order:" <<endl;
		printTreePost(root);
	}
}

void BST::printTreePost(BSTNode *node) {
    if (node == nullptr) {
        return;
    }
    printTreePost(node->left);
    printTreePost(node->right);
    node->printNode(false);
}

void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void BST::clearTree(BSTNode *node) {
	if (node == NULL) {
		return;
	}
	else {
		clearTree(node->left);
		node->left = NULL;
		clearTree(node->right);
		node->right = NULL;
		node->printNode(true);
		delete node;
	}
}

bool BST::checkOut(string title, string author) {
    BSTNode *current = root;
    while (current != nullptr) {
        if (current->book->title == title && current->book->author == author && not current->book->checked_out) {
            current->book->checked_out = true;
            return true;  }
        else if (current->book->author <= author) {
            current = current->right; }
        else {
            current = current->left; }
    }
    return false;
}

bool BST::checkIn(string title, string author) {
    BSTNode *current = root;
    while (current != nullptr) {
        if (current->book->title == title && current->book->author == author && current->book->checked_out) {
            current->book->checked_out = false;
            return true;  }
        else if (current->book->author <= author) {
            current = current->right; }
        else {
            current = current->left; }
    }
    return false;
}

void BST::updateRating(string title, string author, float newRating) {
    BSTNode *current = root;
    while (current != nullptr) {
        if (current->book->title == title && current->book->author == author) {
            current->book->rating = newRating;
            if (current->book->author <= author) {
                current = current->right; }
            else {
                current = current->left; }
        }
        else if (current->book->author <= author) {
            current = current->right; }
        else {
            current = current->left; }
    }
    return;
}


BSTNode *BST::removeNoKids(BSTNode *node) {
    BSTNode *current = root;
    while (current != nullptr) {
        if (*current->book == *node->book) {
            if (current == root) {
                root = NULL;
                return current;
            }

            else if (*current->book > *current->parent->book) {
                current->parent->height = 1;
                setHeight(current->parent);
                current->parent->right = nullptr;
                return current;
            }
            else {
                current->parent->height = 1;
                setHeight(current->parent);
                current->parent->left = nullptr;
                return current;
            }
        }

        else if (*current->book <= *node->book) {
            current = current->right; }
        else {
            current = current->left; }
    }
    return nullptr;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
    BSTNode *current = root;
    while (current != nullptr) {
        if (current == node) {
            if (current == root) {
                if (not leftFlag) {
                    current->right->parent= nullptr;
                    root = current->right;
                    BSTNode *newNode = current;
                    while (newNode->left or newNode->right) {
                        if (newNode->left) {
                            if (newNode->right) {
                                if (newNode->left->height > newNode->right->height) {
                                    newNode = newNode->left;
                                }
                                else {
                                    newNode = newNode->right;
                                }
                            }
                            else {
                                newNode = newNode->left;
                            }
                        }
                        else if (newNode->right) {
                            newNode = newNode->right;
                        }

                    }
                    setHeight(newNode);
                    return current;
                }
                else {
                    current->left->parent= nullptr;
                    root = current->left;
                    BSTNode *newNode = current;
                    while (newNode->left or newNode->right) {
                        if (newNode->left) {
                            if (newNode->right) {
                                if (newNode->left->height > newNode->right->height) {
                                    newNode = newNode->left;
                                }
                                else {
                                    newNode = newNode->right;
                                }
                            }
                            else {
                                newNode = newNode->left;
                            }
                        }
                        else if (newNode->right) {
                            newNode = newNode->right;
                        }

                    }
                    setHeight(newNode);
                    return current;
                }
            }
            else if (*current->book >= *current->parent->book) {
                if (not leftFlag) {
                    current->parent->right = current->right;
                    current->right->parent=current->parent;
                    setHeight(current->right);
                    return current;
                }
                else {
                    current->parent->right = current->left;
                    current->left->parent=current->parent;
                    setHeight(current->left);
                    return current;
                }

            }
            else {
                if (not leftFlag) {
                    current->parent->left = current->right;
                    current->right->parent=current->parent;
                    setHeight(current->right);
                    return current; }
                else {
                    current->parent->left = current->left;
                    current->left->parent=current->parent;
                    setHeight(current->left);
                    return current; }
            }
        }
        else if (*current->book <= *node->book) {
            current = current->right; }
        else {
            current = current->left; }
    }
    return nullptr;
}

BSTNode *BST::remove(string title, string author) {
    BSTNode *currentNode = find(title,author,root);

    if (currentNode == NULL) {
        return NULL;
    }

    BSTNode *current = new BSTNode();
    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        return removeNoKids(currentNode);
    }
    if (currentNode->left != nullptr && currentNode->right == nullptr) {
        return removeOneKid(currentNode, true); }
    if (currentNode->left == nullptr && currentNode->right != nullptr) {
        return removeOneKid(currentNode,false); }
    else {
        if (currentNode == root) {
            current = currentNode->right;
            while (current->left != nullptr) {
                current = current->left;
            }
            if (current->parent == currentNode) {
                root = current;
                current->left=currentNode->left;
                current->parent=nullptr;
                currentNode->left->parent=current;
                setHeight(current->left);
                return currentNode;
            }
            else {
                current->parent->left = nullptr;
                setHeight(current->parent);
                current->parent = nullptr;
                root = current;
                current->left = currentNode->left;
                currentNode->left->parent = current;
                current->right = currentNode->right;
                currentNode->right->parent = current;
                setHeight(current->left);
                return currentNode;
            }
        }
        current = currentNode->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        if (current->parent == currentNode) {
            current->parent=currentNode->parent;
            current->left = currentNode->left;
            currentNode->left->parent = current;
            if (*currentNode->book < *currentNode->parent->book) {
                currentNode->parent->left = current;
            }
            else {
                currentNode->parent->right = current;
            }
            setHeight(current->left);
            return currentNode;
        }
        else {
            current->parent->left = nullptr;
            setHeight(current->parent);
            current->parent = currentNode->parent;
            current->left = currentNode->left;
            currentNode->left->parent = current;
            current->right = currentNode->right;
            currentNode->right->parent = current;
            if (*currentNode->book <= *currentNode->parent->book) {
                currentNode->parent->left = current;
            }
            else {
                currentNode->parent->right = current;
            }
            setHeight(current->left);
            return currentNode;
        }
    }
        /*if (current->parent != currentNode) {
            current->parent->left = nullptr;
            current->left = currentNode->left;
            current->right = currentNode->right;
        }
        if (current->parent == currentNode) {
            current->parent->right=nullptr;
            current->left = currentNode->left;

        }
        if (currentNode == root) {
            root = current;
        }
        else if (currentNode->book < currentNode->parent->book) {
            currentNode->parent->left = current;
        }
        else {
            currentNode->parent->right = current;
        }
        current->parent = currentNode->parent;
        return currentNode;

    }*/
	return nullptr;
}

void BST::setHeight(BSTNode *node) {
    while (node->parent != nullptr) {
        int nodeHeightLeft = 0;
        int nodeHeightRight = 0;
        if (node->parent->left) {
            nodeHeightLeft = node->parent->left->height;
        }
        if (node->parent->right ) {
            nodeHeightRight = node->parent->right->height;
        }
        int biggerHeight = 0;
        if (nodeHeightLeft > nodeHeightRight) {
            biggerHeight = nodeHeightLeft;
        }
        if (nodeHeightRight >= nodeHeightLeft) {
            biggerHeight = nodeHeightRight;
        }
        if (node->parent->height != biggerHeight + 1) {
            node->parent->height = biggerHeight + 1;
            node = node->parent;
        }
        else {
            return;
        }
    }


	
}