#include <stdio.h>
#include <stdlib.h>
struct Node {
    int key;
    struct Node *left , *right;
};
struct Node* create_node(int value) {
    struct Node* node = malloc(sizeof(struct Node));
    node->key = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct Node* insert(struct Node* root,int value) {
    if (root==NULL)
            return create_node(value);
    if (value > root->key)
        root->right = insert(root->right , value);
    else
        root->left = insert(root->left , value);
    return root;

}
void preorder(struct Node* root) {
    if (root==NULL)
        return;
    printf("%d " , root->key);
    preorder(root->left);
    preorder(root->right);
}
void inorder(struct Node* root) {
    if (root==NULL)
        return;
    inorder(root->left);
    printf("%d " , root->key);
    inorder(root->right);
}
void postorder(struct Node* root){
    if (root==NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d " , root->key);
}
struct Queue {
    struct Node** data;
    int front , rear , size;
};
struct Queue* create_queue(int max_size) {
    struct Queue* q = malloc(sizeof(struct Queue));
    q->data = malloc(sizeof(struct Node*)*max_size);
    q->front= 0;
    q->rear = 0;
    q->size=0;
    return q;
}
void enqueue(struct Queue* q, struct Node* node) {
    q->data[q->rear++] = node;
    q->size++;
}
struct Queue* dequeue(struct Queue* q) {
    q->size--;
    return q->data[q->front++];
}
int is_empty(struct Queue* q) {
    return q->size == 0;
}
void bfs(struct Node* root) {
    if (root==NULL)
        return;
    struct Queue* q = create_queue(100);
    enqueue(q,root);
    while (!is_empty(q)) {
        struct Node* node = dequeue(q);
        printf("%d " , node->key);
        if (node->left != NULL)
            enqueue(q , node->left);
        if (node->right != NULL)
            enqueue(q , node->right);
    }
}
struct Node* search(struct Node* root , int key) {
    if (root==NULL)
        return NULL;
    if (root->key==key)
        return root;
    if (root->key>key)
        return search(root->left , key);
    else
        return search(root->right , key);
}
struct Node* find_min(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}
struct Node* find_max(struct Node* node) {
    while (node->right != NULL)
        node = node->right;
    return node;
}
struct Node* delete(struct Node* root , int key) {
    if (root==NULL)
        return root;
    if (key<root->key)
        root->left = delete(root->left , key);
    else if (key>root->key)
        root->right = delete(root->right , key);
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        if (root->left == NULL){
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        if (root->left != NULL && root->right != NULL) {
            struct Node* temp = find_min(root->right);
            root->key = temp->key;
            root->right = delete(root->right , temp->key);
        }
    }
    return root;
}
int main() {
    struct Node* root=NULL;
    while (1) {
        int choice;
        printf("1.Create BST\n"
            "2.Insert element\n"
            "3.Preorder(NLR)\n"
            "4.Inorder(LNR)\n"
            "5.Postorder(LRN)\n"
            "6.BFS\n"
            "7.Search\n"
            "8.Delete\n"
            "9.Find min element\n"
            "10.Find max element\n"
            "11.Exit\n");
        scanf("%d" , &choice);
        switch (choice) {
            case 1: {
                printf("Enter numbers(-1 to stop)\n");
                while (1) {
                    int number;
                    scanf("%d" , &number);
                    if (number==-1)
                        break;
                    root = insert(root , number);
                }
                break;
            }
            case 2: {
                printf("Enter 0 for root , 1 for element:");
                int choice1;
                scanf("%d" , &choice1);
                if (choice1==0) {
                    int root_value;
                    printf("Enter your root:");
                    scanf("%d" , &root_value);
                    root = create_node(root_value);
                }
                else if (choice1==1) {
                    int  element_value;
                    if (root==NULL) {
                        printf("Tree is empty!\n");
                        break;
                    }
                    printf("Enter your element:");
                    scanf("%d" , &element_value);
                    root = insert(root , element_value);
                }
                break;
            }
            case 3: {
                preorder(root);
                printf("\n");
                break;
            }
            case 4: {
                inorder(root);
                printf("\n");
                break;
            }
            case 5: {
                postorder(root);
                printf("\n");
                break;
            }
            case 6: {
                bfs(root);
                printf("\n");
                break;
            }
            case 7: {
                int key;
                printf("Enter your key:");
                scanf("%d" , &key);
                struct Node* result = search(root, key);
                if (result!=NULL)
                    printf("Found : %d\n", result->key);
                else
                    printf("Not found\n");
                break;
            }
            case 8:
                int key;
                printf("Enter your key:");
                scanf("%d" , &key);
                root = delete(root , key);
                printf("Successful delete\n");
                printf("BST after delete:\n");
                inorder(root);
                printf("\n");
                break;
            case 9:
                struct Node* min = find_min(root);
                if (min!=NULL)
                    printf("Min = %d\n",min->key );
                break;
            case 10:
                struct Node* max = find_max(root);
                if (max!=NULL)
                    printf("Max= %d\n" , max->key);
                break;
        }
        if (choice==11)
            break;
    }
}