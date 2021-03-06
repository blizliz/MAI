#include "TAVLTree.h"
#include <iostream>


char NODE = 'y';
char END = 'n';

const size_t LEN_KEY = 256;  // Max length of key-string

TAVLTree::TAVLTree() {
    root = nullptr;
}

TNode * TAVLTree::CreateNode(TData data) {
    TNode *node = (TNode *)malloc(sizeof(TNode));
    node->data = (TData *)malloc(sizeof(TData));
    node->data->key = (char *)malloc(sizeof(char) * (strlen(data.key) + 1));
    strcpy(node->data->key, data.key);
    node->data->value = data.value;
    node->height = 1;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

int TAVLTree::GetHeight(TNode *node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->height;
    }
}

int TAVLTree::BalFact(TNode* node) {
    return GetHeight(node->right)-GetHeight(node->left);
}

void TAVLTree::SetHeight(TNode *node) {
    uint8_t hl = GetHeight(node->left);
    uint8_t hr = GetHeight(node->right);
    if (hl > hr) {
        node->height = hl + 1;
    } else {
        node->height = hr + 1;
    }
}

TNode *TAVLTree::Balance(TNode *node) {

    SetHeight(node);
    if (BalFact(node) == 2) {
        if (BalFact(node->right) < 0) {
            node->right = RotateRight(node->right);
        }
        node = RotateLeft(node);
    } else if (BalFact(node) == -2) {
        if (BalFact(node->left) > 0) {
            node->left = RotateLeft(node->left);
        }
        node = RotateRight(node);
    }
    return node;
}

TNode *TAVLTree::RotateLeft(TNode *q) {
    TNode* p = q->right;
    q->right = p->left;
    p->left = q;
    SetHeight(q);
    SetHeight(p);
    return p;
}

TNode *TAVLTree::RotateRight(TNode *p) {
    TNode* q = p->left;
    p->left = q->right;
    q->right = p;
    SetHeight(p);
    SetHeight(q);
    return q;
}

TNode *TAVLTree::Min(TNode *node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

TNode *TAVLTree::InsertSub(TNode *node, TData data) {

    if(node == nullptr) {
        node = CreateNode(data);
    } else {
        int cmpRes = strcmp(node->data->key, data.key);
        if (cmpRes == 0) {
        } else if (cmpRes > 0) {
            node->left = InsertSub(node->left, data);
        } else {
            node->right = InsertSub(node->right, data);
        }
        node = Balance(node);
    }
    return node;
}

void TAVLTree::Insert(TData data) {

    if(root == nullptr) {
        root = CreateNode(data);
    } else {
        int cmpRes = strcmp(root->data->key, data.key);
        if (cmpRes == 0) {
        } else if (cmpRes > 0 ) {
            root->left = InsertSub(root->left, data);
        } else {
            root->right = InsertSub(root->right, data);
        }
        root = Balance(root);
    }
}

TNode *TAVLTree::DelMin(TNode *node) {
    if( node->left == nullptr )
        return node->right;
    node->left = DelMin(node->left);
    return Balance(node);
}

TNode *TAVLTree::DeleteSub(TNode *node, TData data) {
    if (node == nullptr) {
    } else {
        int cmpRes = strcmp(node->data->key, data.key);
        if (cmpRes > 0) {
            node->left = DeleteSub(node->left, data);
        } else if (cmpRes < 0) {
            node->right = DeleteSub(node->right, data);
        } else {
            TNode *l = node->left;
            TNode *r = node->right;
            free(node->data->key);
            free(node->data);
            free(node);
            node = nullptr;
            if (r == nullptr) {
                return l;
            }
            TNode *min = Min(r);
            min->right = DelMin(r);
            min->left = l;
            return Balance(min);
        }

    }
    return Balance(node);

}

void TAVLTree::Delete(TData data) {
    if (root == nullptr) {
    } else {
        int cmpRes = strcmp(root->data->key, data.key);
        if (cmpRes > 0) {
            root->left = DeleteSub(root->left, data);
        } else if (cmpRes < 0) {
            root->right = DeleteSub(root->right, data);
        } else {
            TNode *l = root->left;
            TNode *r = root->right;
            free(root->data->key);
            free(root->data);
            free(root);
            root = nullptr;
            if (r == nullptr) {
                root = l;
                return;
            }
            TNode *min = Min(r);
            min->right = DelMin(r);
            min->left = l;
            root = Balance(min);
        }
        root = Balance(root);
    }

}

bool TAVLTree::SearchSub(TNode *&node, TData &data) {
    if (node == nullptr) {
        return false;
    } else {
        int cmpRes = strcmp(node->data->key, data.key);
        if (cmpRes > 0) {
            if (!SearchSub(node->left, data)) {
                return false;
            }
        } else if (cmpRes < 0) {
            if (!SearchSub(node->right, data)) {
                return false;
            }
        } else {
            data.value = node->data->value;
            return true;
        }

    }
    return true;
}

bool TAVLTree::Search(TData &data) {
    TNode *node = root;
    if (node == nullptr) {
        return false;
    } else {
        int cmpRes = strcmp(node->data->key, data.key);
        if (cmpRes > 0) {
            if (!SearchSub(node->left, data)) {
                return false;
            }
        } else if (cmpRes < 0) {
            if (!SearchSub(node->right, data)) {
                return false;
            }
        } else {
            data.value = node->data->value;
            return true;
        }
    }
    return true;
}

bool TAVLTree::Serialize(const char* filename) {


    FILE *f = fopen(filename, "wb");

    if (f == nullptr) {
        return false;
    }

    if (root == nullptr) {
        if (fwrite(&END, sizeof(char), 1, f) != 1) {
            return false;
        }
        return true;
    }

    bool ser = SerializeSub(f, root);

    fclose(f);

    return ser;
}

bool TAVLTree::SerializeSub(FILE *f, TNode *node) {

    if (node == nullptr) {
        if (fwrite(&END, sizeof(char), 1, f) != 1) {
            return false;
        }
        return true;
    }

    size_t length = strlen(node->data->key);

    fwrite(&NODE, sizeof(char), 1, f);

    fwrite(&length, sizeof(length), 1, f);
    fwrite(node->data->key, sizeof(char), length, f);
    fwrite(&node->data->value, sizeof(node->data->value), 1, f);
    fwrite(&node->height, sizeof(node->height), 1, f);

    if (!SerializeSub(f, node->left)) {
        return false;
    }

    if (!SerializeSub(f, node->right)) {
        return false;
    }

    return true;
}

bool TAVLTree::Deserialize(const char* filename) {

    FILE *f = fopen(filename, "rb");

    if (f == nullptr) {
        fclose(f);
        return false;
    }

    if(root) {
        DeleteNode(root);
    }

    bool deSer = DeserializeSub(f, root);

    fclose(f);

    return deSer;
}

bool TAVLTree::DeserializeSub(FILE *f, TNode *&node) {

    char mark;
    fread(&mark, sizeof(char), 1, f);

    if (mark == NODE) {

        TData data;
        size_t length;
        uint8_t height;

        fread(&length, sizeof(length), 1, f);
        data.key = (char *)malloc(sizeof(char) * (length + 1));
        fread(data.key, sizeof(char), length, f);
        data.key[length] = '\0';
        fread(&data.value, sizeof(data.value), 1, f);
        fread(&height, sizeof(height), 1, f);

        node = CreateNode(data);
        node->height = height;

        free(data.key);

    } else {
        return true;
    }

    if (!DeserializeSub(f, node->left)) {
        return false;
    }

    if (!DeserializeSub(f, node->right)) {
        return false;
    }

    return true;

}

void TAVLTree::DeleteNode(TNode *&node) {

    if (node->left) {
        DeleteNode(node->left);
    }

    if (node->right) {
        DeleteNode(node->right);
    }

    free(node->data->key);
    free(node->data);
    free(node);
    node = nullptr;
}

void TAVLTree::Erase() {
    if (root) {
        DeleteNode(root);
    }
}

TAVLTree::~TAVLTree() {
    Erase();
}

void TAVLTree::PrintTree(TNode *t)
{
    static int l=0;
    l++;
    if(t) {
        PrintTree(t->right);
        for(int i = 0; i < l; i++)printf("    ");
        printf("\\__%s\n",t->data->key);
        PrintTree(t->left);
    }
    l--;
}