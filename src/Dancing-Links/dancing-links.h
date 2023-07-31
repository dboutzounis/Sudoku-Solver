/* This file includes the struct and the functions for implementing Dancing Links */

#pragma once

#ifndef CODE_DANCING_LINKS_H
#define CODE_DANCING_LINKS_H

typedef struct node {
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    Node *colHead;
    int size;
    int id[3];
} Node;

typedef Node *NodePtr;

NodePtr chooseColumn(NodePtr);
void cover(NodePtr);
void uncover(NodePtr);

#endif // CODE_DANCING_LINKS_H