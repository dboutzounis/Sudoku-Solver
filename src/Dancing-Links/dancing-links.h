/* This file includes the struct and the functions for implementing Dancing Links */

#pragma once

#ifndef CODE_DANCING_LINKS_H
#define CODE_DANCING_LINKS_H

typedef struct node {
    struct node *left;
    struct node *right;
    struct node *up;
    struct node *down;
    struct node *colHead;
    int size;
    int id[3];
} Node;

typedef Node *NodePtr;

NodePtr chooseColumn(NodePtr);
void cover(NodePtr);
void uncover(NodePtr);

#endif // CODE_DANCING_LINKS_H