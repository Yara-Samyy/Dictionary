#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *data;
    struct Node*left;
    struct Node*right;
} Node;

Node* newnode(char* word)
{
    Node*n=malloc(sizeof(Node));
    n->data = malloc(strlen(word) + 1);
    strcpy(n->data, word);
    n->left=NULL;
    n->right=NULL;
    return n;
}

int max (int x, int y)
{
    return x>y?x:y;
}
int height (Node* root)
{
    if(!root)
        return -1;
    else
        return 1 + max(height(root->left),height(root->right));
}

int count(Node* root)
{
    if(!root)
        return 0;
    else return 1 + count (root->left) + count(root->right);
}

Node *insert(Node *root,char *word)
{
    if(root==NULL)
        root=newnode(word);
    if(strcasecmp(word,root->data)<0)
        root->left=insert(root->left,word);
    else if(strcasecmp(word,root->data)>0)
        root->right=insert(root->right,word);
    return root;
}

Node* findmin (Node *root)
{
    if (root == NULL)
        return NULL;
    else if (root ->left == NULL)
        return root;
    else
        return findmin (root->left);
}
Node* findmax (Node *root)
{
    if (root == NULL)
        return NULL;
    else if (root ->right == NULL)
        return root;
    else
        return findmax (root->right);
}
Node*search_last(Node*root, char *value)
{
    Node *last = NULL;
    while (root != NULL)
    {
        last = root;
        if (strcasecmp(root->data, value) == 0)
            return root;
        else if (strcasecmp(value, root->data) < 0)
            root = root->left;
        else
            root = root->right;
    }
    return last;
}

Node* search (Node*root,char * value)
{
    if (root == NULL)
        return NULL;
    else if (strcasecmp(root->data,value)==0)
        return root;
    else if (strcasecmp(value,root->data)<0)
        return search ( root->left,value);
    else
        return search (root->right, value);
}

Node* Getsuccessor(Node* root, char* key)
{
    Node* successor=NULL;
    Node* temp=root;
    while (temp)
    {
        if (strcasecmp(key, temp->data) < 0)
        {
            successor = temp;
            temp = temp->left;
        }
        else if (strcasecmp(key, temp->data) > 0)
            temp = temp->right;
        else if(temp->right)
            return findmin(temp->right);
        else
            return successor;
    }
    return NULL;
}

Node* Getpredecessor(Node*root,char *data)
{
    Node* pre=NULL;
    Node* temp=root;
    while(temp)
    {
        if(strcasecmp(data,temp->data)>0)
        {
            pre=temp;
            temp=temp->right;
        }
        else if(strcasecmp(data,temp->data)<0)
            temp=temp->left;
        else if(temp->left!=NULL)
            return findmax(temp->left);
        else return pre;
    }
    return NULL;
}
int main()
{
    FILE*f1=fopen("Dictionary.txt","r");
    if(f1!=NULL)
        printf("Dictionary loaded successfully...!\n");
    else
    {
        printf("error");
        exit(0) ;
    }
    Node*root=NULL;
    char word[30];
    while (fgets(word, sizeof(word), f1) != NULL)
    {
        word[strcspn(word, "\n")] = '\0';
        root = insert(root, word);
    }
    fclose(f1);
    printf(".......................................\n");
    printf("Size = %d\n", count(root));
    printf(".......................................\n");
    printf("Height = %d\n", height(root));
    printf(".......................................\n");
    char sentence[1000];
    printf("Enter sentence :\n");
    fgets(sentence, sizeof(sentence), stdin);
    char *token = strtok(sentence, " \n");
    while (token)
    {
        Node *k = search(root, token);
        if (k)
            printf("%s - Correct\n", token);
        else
        {
            Node*last=search_last(root,token);
            Node*successor=Getsuccessor(root,last->data);
            Node*predecessor=Getpredecessor(root,last->data);

            printf("%s - Incorrect, Suggestions : %s %s %s \n", token,last->data,successor->data,predecessor->data);
        }
        token = strtok(NULL, " \n");
    }
    return 0;
}
