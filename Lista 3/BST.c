#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int val;
    struct node * left;
    struct node *right;
} node;

typedef node *arvore;

node * rotate_left(node * root){
    node * R;
    node * RL;
    R = root->right;
    RL = R->left;
    R->left = root;
    root->right = RL;
    return R;
}

node * rotate_right(node * root){
    node * R;
    node * RL;
    R = root->left;
    RL = R->right;
    R->right = root;
    root->left = RL;
    return R;
}

node * bst_search(node * root, int v, int * nop, int * rot){
    if (root == NULL){
        printf("%d\n", *nop); 
        *rot = 0;     
        return NULL;
    } else if (v == root->val){
        printf("%d\n", *nop);       
        //root = splay(root, v);
        return root;
    } else if (v < root->val){
        *nop += 1;
        root->left = bst_search(root->left, v, nop, rot);
        if ((*rot) == 1){
            root = rotate_right(root);
        }
        return root;
    } else {
        *nop += 1;       
        root->right = bst_search(root->right, v, nop, rot);
         if ((*rot) == 1){
            root = rotate_left(root);
        }
        return root;
    }
}

node * bst_insert(node * root, int val, int * nop){
    if (root == NULL){
        node * novo;
        novo = malloc(sizeof(node));
        novo->val = val;
        novo->left = novo->right = NULL;
        printf("%d\n", *nop);
        return novo;
    }else if(root->val == val){
        printf("%d\n", *nop);
        return root;
    } else if (val < root->val){
         *nop += 1;
        root->left = bst_insert(root->left, val, nop);
        root = rotate_right(root);
        return root;
    } else {
       *nop += 1;
        root->right = bst_insert(root->right, val, nop);
        root = rotate_left(root);
        return root;
    }
    printf("%d\n", *nop);
    return root;
}

node * bst_delete_min(node * root, int * v){
    if (root->left == NULL){
        node * R;
        R = root->right;
        *v = root->val;
        free(root);
        return R;
    } else {
        node * L;
        L = bst_delete_min(root->left, v);
        root->left = L;
        return root;
    }
}

node * bst_delete(node * root, int v, int * nop, int * rot, int *root_val, int * aux){
    //*nop += 1;
    if (root == NULL){
        *rot = 0;
        printf("%d\n", *nop);
        return NULL;
    } else if (v < root->val){
        *nop+=1;
        root->left = bst_delete(root->left, v, nop, rot, root_val, aux);
        if(root->left == NULL || root->left->val == *aux){
            (*root_val) = root->val;
        }else if(root->left->val == (*root_val) && (*rot) == 1){
            root = rotate_right(root);
        }
        return root;
    } else if (v > root->val){
        *nop+=1;
        root->right = bst_delete(root->right, v, nop, rot, root_val, aux);
        if(root->right == NULL || root->right->val == *aux){
            (*root_val) = root->val;
        }else if(root->right->val == (*root_val) && (*rot) == 1){
            root = rotate_left(root);
        }
        return root;
    } else if(root->val == v){
        printf("%d\n", *nop);
        if((root->left) == NULL){
            node * r;
            r = root->right;
            free(root);
            if(r != NULL){
                *aux = r->val;
            }
            return r;
        } else if(root->right == NULL){
            node * L;
            L = root->left;
            free(root);
             if(L != NULL){
                *aux = L->val;
            }
            return L;
        }else {
            root->right = bst_delete_min(root->right, &root->val);
            *aux = root->val;
            return root;
        }
    }
}

void pre_order(node * root){
    if (root == NULL){
        return;
    }
    printf("%d ", root->val);
    pre_order(root->left);
    pre_order(root->right);
}


int main(void){
    char op[4];
    node * root;
    root = NULL;

    int v;
    int num_op;
    int num_rot;
    int aux, root_val;



    do
    {

       num_op = 0;
       num_rot = 1;

      scanf(" %s", op);

      if (strcmp(op, "INS") == 0){
            scanf(" %d", &v);       
            root = bst_insert(root, v, &num_op);           
      }else if (strcmp(op, "FND") == 0){  
            scanf(" %d", &v);            
            root = bst_search(root, v, &num_op, &num_rot);       
      }else if (strcmp(op, "DEL") == 0){
            scanf(" %d", &v);
            root = bst_delete(root, v, &num_op, &num_rot, &root_val, &aux);
       }else if (strcmp(op, "DEB") == 0){
            pre_order(root);
       }
    } while (strcmp(op, "END") != 0);
    


    return 0;

} 