#include<stdio.h>
#include<stdlib.h>

#define COUNT 10
//Definujeme prvok BVS
struct node{
    int data;
    struct node* left;
    struct node* right;
};
void print2DUtil(struct node *root, int space){
    if (root == NULL)
        return;
    space += COUNT;
    print2DUtil(root->right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n",root->data);
    print2DUtil(root->left, space);
}
void print2D(struct node *root)
{
    print2DUtil(root, 0);
}
struct node* splay(struct node** root, int searchedValue);
//Allokujeme pamat pre prvok 
//a nastavime jeho hodnoty na NULL, pretoze to je list
struct node* createNode(int value){
    struct node* newNode = malloc(sizeof(struct node));
    if(newNode!=NULL){
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}
//Ako vstup vkladame hlavicku BVS
//funkcia vypise hodnoty zoradene od najmensieho po najvacsi
void inorder(struct node* tempNode){
    if(tempNode==NULL)
        return;
    inorder(tempNode->left);
    printf("%d, ",tempNode->data);
    inorder(tempNode->right);
}
//Rekurzivne prejdeme kazdy prvok a uvolnime ho z pamate
void freeTree(struct node* tempNode){
    if(tempNode==NULL)
        return;
    freeTree(tempNode->left);
    free(tempNode);
    freeTree(tempNode->right);
}
//funkcia na pridanie elementu do binarneho stromu
void insertion(struct node** root, int addedData){
    if((*root) == NULL){
        //Ak je hlavicka prazdna nastavime jej hodnotu
        (*root) = createNode(addedData);
        return;
    }
    //Ak sa hodnota uz nachadza v strome, nic sa nestane
    if(addedData==(*root)->data){
        return;
    }
    //Rekurzivne prechadzame prvky stromu podla < >
    if(addedData<(*root)->data){
        return insertion(&((*root)->left), addedData);
    }
    else if(addedData>(*root)->data){
        return insertion(&((*root)->right), addedData);
    }
    
}
//Funkcia na najdenie prvku v strome
struct node* search(struct node* root, int searchedNumber){
    return splay(&root, searchedNumber);
}
//Funkcia, ktora nam vrati rodica podla vstupnej hodnoty
struct node* getParentNode(struct node* root, int value){
    //ak hladany rodic je nasa zaciatocna hodnota
    if(root==NULL || root->data==value)
        return root;
    if(((root->left!=NULL)&&(root->left->data==value))||((root->right!=NULL)&&(root->right->data==value))){
        return root;
    }
    struct node* parent = getParentNode(root->left, value);
    if(parent!=NULL)
        return parent;
    parent = getParentNode(root->right, value);
    return parent;
}
//Funkcia na vratenie najmensej hodnoty pod vstupnou hodndotou
struct node* minValue(struct node* searchedNode){
    while(searchedNode && searchedNode->left !=NULL)
        searchedNode=searchedNode->left;
    return searchedNode;
}
//Vymazeme hodnotu v strome podla vstupnej hodnoty
struct node* delete(struct node* root, int dataToDelete){
    if(root==NULL)
        return root;
    //Rekurzivne prehladavame strom
    if(dataToDelete<root->data)
        root->left = delete(root->left,dataToDelete);    
    else if(dataToDelete>root->data)
        root->right = delete(root->right,dataToDelete);
    else{
        //Ak najdeme hodnotu, ktoru chceme vymazat, musime pocitat so 4 moznostami
        //Moznost kedy vymazavame list
        if(root->left==NULL && root->right==NULL){
            free(root);
            return NULL;
        }
        else if(root->left==NULL || root->right==NULL){
            struct node *temp;
            if(root->left==NULL)
                temp = root->right;
            else
                temp = root->left;
            free(root);
            return temp;
        }
        else{
            struct node* temp = minValue(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}
struct node* rightRH(struct node* A){
    struct node* B=A->left;
    A->left=B->right;
    B->right=A;
    return B;
}
struct node* leftLH(struct node* A){
    struct node* B = A->right;
    A->right=B->left;
    B->left=A;
    return B;
}
struct node* splay(struct node** root, int data){
    if((*root)==NULL || (*root)->data==data)
        return (*root);
    if((*root)->data>data){
        if((*root)->left==NULL)
            return (*root);
        if((*root)->left->data>data){
            (*root)->left->left=splay(&(*root)->left->left, data);
            (*root)=rightRH((*root));
        }
        else if((*root)->left->data<data){
            (*root)->left->right = splay(&(*root)->left->right, data);
            if ((*root)->left->right != NULL)
                (*root)->left = leftLH((*root)->left);
        }
        return ((*root)->left == NULL)? (*root): rightRH((*root));
    }
    else{
        if ((*root)->right == NULL)
            return (*root);
        if ((*root)->right->data > data){
            (*root)->right->left = splay(&(*root)->right->left, data);
            if ((*root)->right->left != NULL)
                (*root)->right = rightRH((*root)->right);
        }
        else if ((*root)->right->data < data){
            (*root)->right->right = splay(&(*root)->right->right, data);
            (*root) = leftLH((*root));
        }
        return ((*root)->right == NULL)? (*root): leftLH((*root));
    }
}
int main(){
    int rootValue;
    int inputValue;
    int deleteValue;
    int searchValue;
    int i=0,j=0;
    printf("Vloz hodnotu hlavicky binarneho stromu\n");
    scanf("%d",&rootValue);
    struct node* root = createNode(rootValue);
    while(i==0){
        j=0;
        printf("Vloz hodnotu do binarneho stromu\nAk vlozis %d, vkladanie sa zrusi\n",rootValue);
        scanf("%d",&inputValue);
        if(inputValue==rootValue){
            while(j==0){
                printf("Vloz 1 ak chces vypisat hodnoty stromu\nVloz 2 ak chces vymazat hodnotu v strome\nVloz 3 ak chces najst hodnotu v strome\nVloz 4 ak chces opat vlozit hodnoty do stromu\nVloz ine ak chces ukoncit program\n");
                scanf("%d",&inputValue);
                switch (inputValue){
                    case 1:
                        inorder(root);
                        printf("\n");
                        break;
                    case 2:
                        scanf("%d",&deleteValue);
                        delete(root, deleteValue);
                        root = splay(&root, deleteValue);
                        printf("Hodnota %d bola vymazana\n", deleteValue);
                        break;
                    case 3:
                        scanf("%d",&searchValue);
                        if((root = search(root, searchValue)))
                            printf("Hodnota %d sa nachadza v stome\n",searchValue);
                        else
                            printf("Hodnota %d sa nenachadza v strome\n",searchValue);
                        break;
                    case 4:
                        j=1;
                        break;
                    default:
                        j=1;
                        i=1;
                        break;
                }
            }
        }
        insertion(&root,inputValue);
        root = splay(&root, inputValue);
        print2D(root);
    }
    freeTree(root);
    return 0;
}