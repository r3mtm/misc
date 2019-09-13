/*
    AVL tree operations.
 */

#include<stdio.h>
#include<stdlib.h>

struct tree {
    struct tree *left;
    int data;
    struct tree *right;
    int height;
};

//Inorder tree traversal
void display(struct tree *node){
    if(node->left != NULL){
        display(node->left);
    }
    printf("%d ", node->data);
    if(node->right != NULL){
        display(node->right);
    }
}

//Returns the height of the subtree
int height(struct tree *node){
    if (node==NULL){
        return 0;
    }else{
        return node->height;
    }
}

//Creates a new node
struct tree *createnode(int val){
    struct tree *newnode=(struct tree*)malloc(sizeof(struct tree));
    newnode->data=val;
    newnode->height=1;
    newnode->left=newnode->right=NULL;
    return newnode;
}

//Left Rotation
struct tree *rotateLeft(struct tree *node){
    struct tree *nextRoot=node->right;
    struct tree *leftNode=nextRoot->left;

    nextRoot->left=node;
    node->right=leftNode;

    node->height = 1+((height(node->left) > height(node->right))?height(node->left) : height(node->right));
    nextRoot->height = 1+((height(nextRoot->left) > height(nextRoot->right))?height(nextRoot->left) : height(nextRoot->right));

    return nextRoot;
}

//Right rotation
struct tree *rotateRight(struct tree *node){
    struct tree *rightNode = node->left->right;
    struct tree *nextRoot = node->left;
    nextRoot->right = node; 
    node->left=rightNode;

    node->height = 1+((height(node->left) > height(node->right))?height(node->left) : height(node->right));
    nextRoot->height = 1+((height(nextRoot->left) > height(nextRoot->right))?height(nextRoot->left) : height(nextRoot->right));

    return nextRoot;
}

//Insertion of new node.
struct tree *insert(struct tree *node, int val){
    if(node == NULL){
        return createnode(val);
    }else if(val < node->data){
        node->left=insert(node->left, val);
    }else if(val > node->data){
        node->right=insert(node->right, val);
    }

    node->height = 1+((height(node->left) > height(node->right))?height(node->left) : height(node->right));
    int balFact = height(node->left)-height(node->right);

    if(balFact > 1){
        if(val < node->left->data){
            //LL
            return rotateRight(node);
        }else if(balFact > 1 && val > node->left->data){
            //LR
            node->left=rotateLeft(node->left);
            return rotateRight(node);
        }
    }else if(balFact < -1){
        if(val > node->right->data){
            //RR
            return rotateLeft(node);
        }else if(val < node->right->data){
            //RL
            node->right=rotateRight(node->right);
            return rotateLeft(node);
        }
    }else{
        return node;
    }
}

//Deletion of an existing node.
struct tree *delete(struct tree *node, int val){
    static char update='N'; //To check whether tree is updated.
    if(val < node->data){
        if(node->left == NULL){
            printf("\nNot found\n\n");
            return node;
        }else{
            node->left=delete(node->left, val);
        }
    }else if(val > node->data){
        if(node->right == NULL){
            printf("\nNot found\n\n");
            return node;
        }else{
            node->right=delete(node->right, val);
        }
    }else{
        //delete
        struct tree *pred, *ppred;
        update='Y';
        if(node->left == NULL && node->right == NULL){
            //leaf node
            return NULL;
        }else if(node->left == NULL || node->right == NULL){
            if(node->right == NULL){
                return node->left;
            }else{
                return node->right;
            }
        }else{
            if(node->left != NULL){
                //inorder predecessor
                pred=ppred=node->left;
                while(pred != NULL){
                    if(pred->right == NULL){
                        if(pred->left != NULL){
                            ppred=pred;
                            pred=pred->left;
                        }else{
                            break;
                        }
                    }else{
                        ppred=pred;
                        pred=pred->right;
                    }
                }
                ppred->right=NULL;
                pred->right = node->right;
                if(ppred != pred){
                    pred->left = node->left;
                }
            }/*else if(node->right != NULL){
                //inorder successor
                pred=ppred=node->right;
                while(pred != NULL){
                    if(pred->left == NULL){
                        if(pred->right != NULL){
                            ppred=pred;
                            pred=pred->right;
                        }else{
                            break;
                        }
                    }else{
                        ppred=pred;
                        pred=pred->left;
                    }
                }
                ppred->left=NULL;
                pred->left = node->left;
                if(pred != ppred){
                    pred->right = node->right;
                }
            }*/
            node=pred;
            node->height = 1+((height(node->left) > height(node->right))?height(node->left) : height(node->right));
            int balFact = height(node->left)-height(node->right);

            if(balFact > 1){
                if(val < node->left->data){
                    return rotateRight(node);
                }else{
                    node->left=rotateLeft(node->left);
                    return rotateRight(node);
                }
            }else if(balFact < -1){
                if(val > node->right->data){
                    node->right=rotateRight(node->right);
                    return rotateLeft(node);
                }
            }
        }
    }

    if(update='Y'){
        node->height = 1+((height(node->left) > height(node->right))?height(node->left) : height(node->right));
        int balFact = height(node->left)-height(node->right);

        if(balFact > 1){
            if(val < node->left->data){
                return rotateRight(node);
            }else{
                node->left=rotateLeft(node->left);
                return rotateRight(node);
            }
        }else if(balFact < -1){
            if(val > node->right->data){
                node->right=rotateRight(node->right);
                return rotateLeft(node);
            }
        }
    }
    update='N';
    return node;
}

//Read user input
int readkey(){
    int val;
    printf("Input key =>");
    scanf(" %d", &val);
    return val;
}

int main() {
    int inp;
    struct tree *root = NULL;
    /*int arr[13]={14, 11, 19, 7, 12, 17, 53, 4, 8, 13, 16, 20, 60};
    for(int i=0;i<13;++i){
        root=insert(root, arr[i]);
    }
    root=delete(root, 8);
    root=delete(root, 7);
    root=delete(root, 11);
    */
    while(1){
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Delete\n");
        printf("=>");
        scanf(" %d", &inp);
        if(inp == 1) {
            if(root == NULL){
                root=insert(root, readkey());
            }else{
                root=insert(root, readkey());
            }
        }else if(inp == 2){
            if(root != NULL){
                printf("\n");
                display(root);
                printf("\n\n");
            }else{
                printf("\nEmpty tree\n\n");
            }
        }else if(inp == 3){
            if(root!=NULL){
                root=delete(root, readkey());
                printf("\n\nDeleted\n\n");
            }else{
                printf("\nEmpty tree\n\n");
            }
        }
    }
    return 0;
}