#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

int listPosX = 10; // Global variable to keep track of the X position for the list

// Function to draw a node
void drawNode(Node* node, int x, int y, int offsetX) {
    if (node == nullptr) return;

    // Draw the node
    circle(x, y, 20);
    char buffer[10];
    sprintf(buffer, "%d", node->value);
    outtextxy(x - 5, y - 5, buffer);

    // Draw the left subtree
    if (node->left) {
        line(x, y, x - offsetX, y + 50);
        drawNode(node->left, x - offsetX, y + 50, offsetX / 2);
    }

    // Draw the right subtree
    if (node->right) {
        line(x, y, x + offsetX, y + 50);
        drawNode(node->right, x + offsetX, y + 50, offsetX / 2);
    }
}

// Function to highlight a node and update the list
void highlightNode(Node* node, int x, int y) {
    setfillstyle(SOLID_FILL, RED);
    fillellipse(x, y, 20, 20);
    setcolor(WHITE); // Set text color to white
    char buffer[10];
    sprintf(buffer, "%d", node->value);
    outtextxy(x - 7, y - 7, buffer);

    // Update the list display
    setcolor(WHITE); // Set list text color to white
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    outtextxy(listPosX, getmaxy() - 30, buffer);
    listPosX += 50; // Move the X position for the next node

    delay(1000);
}

// Function to display the traversal message
void displayTraversalMessage(const string& message) {
    setcolor(WHITE); // Set text color to white
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy(getmaxx() / 2 - 150, getmaxy() / 2 + 50, const_cast<char*>(message.c_str()));
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
}

// Traversal functions
void inorder(Node* node, int x, int y, int offsetX) {
    if (node == nullptr) return;
    inorder(node->left, x - offsetX, y + 50, offsetX / 2);
    highlightNode(node, x, y);
    inorder(node->right, x + offsetX, y + 50, offsetX / 2);
}

void preorder(Node* node, int x, int y, int offsetX) {
    if (node == nullptr) return;
    highlightNode(node, x, y);
    preorder(node->left, x - offsetX, y + 50, offsetX / 2);
    preorder(node->right, x + offsetX, y + 50, offsetX / 2);
}

void postorder(Node* node, int x, int y, int offsetX) {
    if (node == nullptr) return;
    postorder(node->left, x - offsetX, y + 50, offsetX / 2);
    postorder(node->right, x + offsetX, y + 50, offsetX / 2);
    highlightNode(node, x, y);
}

void visualizeTraversal(Node* root, void (*traversalFunc)(Node*, int, int, int), const string& traversalType) {
    initwindow(16*45, 9*40, (char*)"Visualization of tree traversal");
    // Initial drawing parameters
    int startX = getmaxx() / 2;
    int startY = 50;
    int offsetX = 200;
    
    // Reset the list position for new traversal
    listPosX = 10;

    // Draw the tree structure
    drawNode(root, startX, startY, offsetX);

    // Display the traversal type message
    displayTraversalMessage(traversalType);

    // Highlight nodes in traversal order
    traversalFunc(root, startX, startY, offsetX);

    getch();
    closegraph();
}

int main() {
	
    // Create a simple binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
	
    // Visualizing In-order Traversal
    visualizeTraversal(root, inorder, "In-order Traversal");

    // Visualizing Pre-order Traversal
    visualizeTraversal(root, preorder, "Pre-order Traversal");

    // Visualizing Post-order Traversal
    visualizeTraversal(root, postorder, "Post-order Traversal");

    return 0;
}
