#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct RB_tree
{
    int data;
    struct RB_tree *right, *left, *parent;
    char color;

} RB_tree;

RB_tree *root_gl = NULL;
void print_in_order(RB_tree *root)
{
    if (root == NULL)
        return;

    print_in_order(root->left);
    printf("%d\n", root->data);
    print_in_order(root->right);
}

int height(RB_tree *root)
{
    if (root == NULL)
        return 0;

    int left = height(root->left);
    int right = height(root->right);

    return left < right ? right + 1 : left + 1;
}

RB_tree *get_uncle(RB_tree *root)
{
    if (root->parent != NULL && root->parent->parent != NULL)
        return root->parent->parent->right == root->parent ? root->parent->parent->left : root->parent->parent->right;
    return NULL;
}
RB_tree *get_grandpa(RB_tree *root)
{
    if (root->parent != NULL)
        return root->parent->parent;
    return NULL;
}

void right_rotate(RB_tree *root)
{
    RB_tree *child=root->left->right;
   
    root->left->right=root; 
    if(root->parent==NULL){
        root_gl=root->left;
        root->left->parent=NULL;
        
    }
    else if(root->parent->right==root){
        
        root->parent->right=root->left;
        root->left->parent=root->parent;
        ;
    }
    else{
        root->parent->left=root->left;
        root->left->parent=root->parent;
    }
    root->parent=root->left;
    root->left=child;
    if(child!=NULL)
        child->parent=root;

}

void left_rotate(RB_tree *root)
{
    RB_tree *child=root->right->left;
    root->right->left=root; 
    if(root->parent==NULL){
        root_gl=root->right;
    }
    else if(root->parent->right==root){//printf("girdi");
        root->parent->right=root->right;

    }
    else{
        root->parent->left=root->right;
    }
    root->right->parent=root->parent;

    root->parent=root->right;
    root->right=child;
    if(child!=NULL)
        child->parent=root;
    //printf("bu: %d\n",root_gl->right->left->data);

}

void case1(RB_tree **root);

void case2(RB_tree *root)
{
    if ((root)->parent->color == 'R' && root->color=='R'){
        RB_tree *uncle = get_uncle(root);
        RB_tree *grandpa = get_grandpa(root);  

        if (uncle == NULL || uncle->color == 'B'){
            //rotasyonlar

            //LL
            if ((root)->parent->left == (root) && grandpa->left == (root)->parent)
            {
                //grandpa yolLA
                
                right_rotate(grandpa);

                (root)->parent->color = 'B';
                root->parent->right->color = 'R';
                case1(&(root)->parent);
            }
            //RR 
            else if ((root)->parent->right == (root) && grandpa->right == (root)->parent){
                //printf("RR data: %d \n",grandpa->data);
                left_rotate(grandpa);
    
                (root)->parent->color = 'B';
                root->parent->left->color = 'R';
                case1(&root->parent); //rootun parentı değişecğinden bu böyle olmıycak !!!
            }
            //RL
            else if(root->parent->left==root && grandpa->right==root->parent){
               
                right_rotate(root->parent); 
                left_rotate(grandpa);printf("giir");
                root->color='B';
                root->left->color='R';
                case1(&root->right);
            }

            //LR
            else if(root->parent->right==root && grandpa->left==root->parent){
                    left_rotate(root->parent);
                    right_rotate(grandpa);

                    root->color='B';
                    root->right->color='R';
                    case1(&root->left);

            }


        }

        else if (uncle->color == 'R'){
            uncle->color = 'B';
            (root)->parent->color = 'B';
            grandpa->color = 'R';
            case1(&grandpa);
            
        }
        

    }
    
}
void case1(RB_tree **root)
{
    if ((*root)->parent == NULL)
    {
        (*root)->color = 'B';
    }
    else
        case2( (*root));
}



void insert(RB_tree **root, int data, RB_tree *parent, RB_tree **bug)
{

    if ((*root) == NULL)
    {
        RB_tree *new = (RB_tree *)malloc(sizeof(RB_tree));
        new->parent = parent;
        new->color = 'R';
        new->data = data;
        new->left = NULL;
        new->right = NULL;
        (*root) = new;
        //RB tree check burda olacak
        case1(&(*root));
        //printf("burda:\n");
        //print_in_order((*root));
        //printf("\n\n");
        return;
    }

    if (data > (*root)->data)
    {
        insert(&(*root)->right, data, (*root), &(*bug));
    }
    else
    {
        insert(&(*root)->left, data, (*root), &(*bug));
    }
}

void print_level_order(RB_tree *root, int level, char side)
{
    if (root == NULL)
        return;

    if (level == 1)
    {
        if (root->parent == NULL)
            printf("%d %c ", root->data, root->color);
        else
        {
            printf("%d %c (%d %c) ", root->data, root->color, root->parent->data, side);
        }
        return;
    }
    else if (level == 0)
    {
        for (int i = 1; i <= height(root); i++)
        {
            print_level_order(root, i, ' ');
            printf("\n");
        }
    }
    else
    {
        print_level_order(root->left, level - 1, 'L');
        print_level_order(root->right, level - 1, 'R');
    }
}

int main()
{

    int data;
    scanf("%d", &data);
    while (data != -1)
    {
        insert(&root_gl, data, NULL, &root_gl);

        scanf("%d", &data);
    }

    //right_rotate(&root);
    print_in_order(root_gl);
    printf("\n");
    print_level_order(root_gl, 0, ' ');
   // printf("height:%d\n", height(root_gl));
    // printf("%d %d",root->right->left->data,get_grandpa(root->right->left)->data);
}
