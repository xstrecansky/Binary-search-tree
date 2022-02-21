#include<stdio.h>
#include<stdlib.h>
//Definujeme prvok BVS
struct node{
    int data;
    struct node* left;
    struct node* right;
};
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
    if(root==NULL||(root->data==searchedNumber))
        return root;
    if(root->data>searchedNumber){
        return search((root->left), searchedNumber);
    }
    return search((root->right), searchedNumber);
}
//Funkcia, ktora nam vrati rodica podla vstupnej hodnoty
struct node* getParentNode(struct node* root, int value){
    if(root->data==value){
        return root;
    }
    else{
        if(value<root->data){
            if(value==root->left->data)
                return root;
            else
                getParentNode(root->left,value);
        }
        if(value>root->data){
            if(value==root->right->data)
                return root;
            else
                getParentNode(root->right, value);
        }
    }
}
//Vymazeme hodnotu v strome podla vstupnej hodnoty
void delete(struct node** root, int dataToDelete){
    //Rekurzivne prehladavame strom
    if(dataToDelete<(*root)->data){
        return delete(&((*root)->left),dataToDelete);
    }
    else if(dataToDelete>(*root)->data){
        return delete(&((*root)->right),dataToDelete);
    }
    else{
        //Ak najdeme hodnotu, ktoru chceme vymazat, musime pocitat so 4 moznostami
        struct node* parent = getParentNode((*root),dataToDelete);
        //Pripad kedy vymazavame list
        if((*root)->left==NULL && (*root)->right==NULL){
            if(parent->data>(*root)->data){
                parent->left=NULL;
                free(*root);
                return;
            }
            else{
                parent->right=NULL;
                free(*root);
                return;
            }
        }
        //TODO:



        
    }
}
int main(){
    int rootValue;
    int inputValue;
    int deleteValue;
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
                        delete(&root, deleteValue);
                        printf("Hodnota bola vymazana\n");
                        break;
                    case 3:
                        scanf("%d",&deleteValue);
                        if(search(root, deleteValue))
                            printf("Hodnota %d sa nachadza v stome\n",deleteValue);
                        else
                            printf("Hodnota %d sa nenachadza v strome\n",deleteValue);
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
    }
    freeTree(root);
    return 0;
}