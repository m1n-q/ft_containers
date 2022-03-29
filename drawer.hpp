#include <algorithm>
// #include <bits/stdc++.h>
#include <cstdio>
#include <graphics.h>
#include <iostream>
#include <sstream>
#include <string>


void display(avl_node* ptr, int level)
{
    int i;
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == _root)
            std::cout << "Root -> ";
        for (i = 0; i < level && ptr != _root; i++) {

            std::cout << "        ";
        }
        int j;

        std::cout << ptr->val.first;
        display(ptr->left, level + 1);
    }
}


void drawNode(avl_node* root,
                       int x, int y,
                       int noderatio)
{
    int bf = get_bf(root);
    if (bf > 1 || bf < -1) {
        setcolor(12);
        outtextxy(600, 10, "Imbalanced!");
        circle(x, y, 25);
        setfillstyle(SOLID_FILL, 12);
    }
    else if (bf == 1 || bf == -1) {
        setcolor(14);
        circle(x, y, 25);
        setfillstyle(SOLID_FILL, 14);
        floodfill(x, y, YELLOW);
    }
    else {
        setcolor(15);
        circle(x, y, 25);
        setfillstyle(SOLID_FILL, 15);
        floodfill(x, y, WHITE);
    }

    char arr[5];
    itoa(root->data, arr, 10);
    outtextxy(x, y, arr);

    if (root->left != NULL) {
        line(x, y, x - 20 * noderatio, y + 70);
        drawNode(root->left, x - 20 * noderatio, y + 70,
                 noderatio - 2);
    }
    if (root->right != NULL) {
        line(x, y, x + 20 * noderatio, y + 70);
        drawNode(root->right, x + 20 * noderatio, y + 70,
                 noderatio - 2);
    }
}

// Function to draw the AVL tree
void avlTree::drawTree(avl_node* root, int x, int y)
{
    settextstyle(10, HORIZ_DIR, 3);
    outtextxy(10, 10, "Tree");
    outtextxy(20, 600, "Balanced : ");
    circle(190, 605, 10);

    // Floodfill(190, 605, WHITE);
    outtextxy(520, 600, "L/R Heavy : ");
    setcolor(14);
    circle(700, 605, 10);

    // Floodfill(700, 605, YELLOW);
    setcolor(15);
    outtextxy(950, 600, "Critical : ");
    setcolor(12);
    circle(1115, 605, 10);

    // Floodfill(1115, 605, RED);

    settextstyle(10, HORIZ_DIR, 2);
    drawNode(root, x, y, 8);
}
