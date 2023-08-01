#include "dancing-links.h"
#include <stdio.h>
#include <stdlib.h>

NodePtr chooseColumn(Node *head) {
    NodePtr column = head->right;
    for (NodePtr j = column->right; j != head; j = j->right) {
        if (j->size < column->size)
            column = j;
    }
    return column;
}

void cover(Node *column) {
    column->left->right = column->right;
    column->right->left = column->left;

    for (NodePtr i = column->down; i != column; i = i->down) {
        for (NodePtr j = i->right; j != i; j = j->right) {
            j->down->up = j->up;
            j->up->down = j->down;
            (j->colHead->size)--;
        }
    }
}

void uncover(Node *column) {
    for (NodePtr i = column->up; i != column; i = i->up) {
        for (NodePtr j = i->left; j != i; j = j->left) {
            (j->colHead->size)++;
            j->down->down->up = j;
            j->up->down = j;
        }
    }

    column->left->right = column;
    column->right->left = column;
}
