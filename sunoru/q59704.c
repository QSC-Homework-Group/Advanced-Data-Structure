/*
 * AVL tree.
 */
#include <stdlib.h>
#include <stdio.h>

typedef struct avl_node {
    int data;
    int height;
    struct avl_node *left, *right, *parent;
} node;
node pool[50];
int used = 0;

node *new_node(node *dummy) {
    node *p = pool + (used++);
    p->data = 0;
    p->height = 0;
    p->left = p->right = NULL;
    p->parent = dummy;
    return p;
}

int get_height(node *p)
{
    if (p == NULL) {
        return -1;
    }
    return p->height;
}

void update_height(node *p)
{
    int l = get_height(p->left);
    int r = get_height(p->right);
    p->height = (l > r ? l : r) + 1;
}

node *ll_rotate(node *root)
{
    node *x = root->left;
    x->parent = root->parent;
    root->parent = x;
    root->left = x->right;
    x->right = root;
    update_height(root);
    update_height(x);
    return x;
}

node *rr_rotate(node *root)
{
    node *x = root->right;
    x->parent = root->parent;
    root->parent = x;
    root->right = x->left;
    x->left= root;
    update_height(root);
    update_height(x);
    return x;
}

node *lr_rotate(node *root)
{
    node *y = root->left;
    node *x = y->right;
    x->parent = root->parent;
    y->parent = root->parent = x;
    y->right = x->left;
    root->left = x->right;
    x->left = y;
    x->right = root;
    update_height(root);
    update_height(y);
    update_height(x);
    return x;
}

node *rl_rotate(node *root)
{
    node *y = root->right;
    node *x = y->left;
    x->parent = root->parent;
    y->parent = root->parent = x;
    y->left = x->right;
    root->right = x->left;
    x->left = root;
    x->right = y;
    update_height(root);
    update_height(y);
    update_height(x);
    return x;
}

int insert(node **root_p, node *p)
{
    int l, r;
    int q = 0, qs = 0;
    node *root = *root_p;
    if (root == NULL) {
        *root_p = p;
        return q;
    }
    if (p->data == root->data) {
        free(p);
        return q;
    } else if (p->data < root->data) {
        qs = insert(&root->left, p);
        q = 1;
    } else {
        qs = insert(&root->right, p);
        q = 2;
    }
    l = get_height(root->left);
    r = get_height(root->right);
    if (abs(l - r) >= 2) {
        if (q == 1) {
            if (qs == 1) {
                *root_p = ll_rotate(root);
            } else if (qs == 2) {
                *root_p = lr_rotate(root);
            }
        } else if (q == 2) {
            if (qs == 1) {
                *root_p = rl_rotate(root);
            } else if (qs == 2) {
                *root_p = rr_rotate(root);
            }
        }
    } else {
        update_height(root);
    }
    return q;
}

int main()
{
    int n, i;
    int x;
    node *dummy;
    node *root, *p;
    for (i = 0; i < 50; ++i) {
        pool[i].data = -1;
        pool[i].height = -1;
        pool[i].parent = NULL;
        pool[i].left = NULL;
        pool[i].right = NULL;
    }

    dummy = new_node(dummy);
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        p = new_node(dummy);
        scanf("%d", &p->data);
        insert(&root, p);
    }
    printf("%d\n", root->data);

    return 0;
}
