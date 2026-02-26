#include "red_black_tree.h"
#include <iostream>

// 节点构造函数
RBNode::RBNode(int val) {
    data = val;
    color = RED; // 新节点默认为红色
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

// 红黑树构造函数
RedBlackTree::RedBlackTree() {
    TNULL = new RBNode(0);
    TNULL->color = BLACK;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

// 支持初始化列表的构造函数
RedBlackTree::RedBlackTree(std::initializer_list<int> list) : RedBlackTree() {
    for (int val : list) {
        insert(val);
    }
}

// 批量构建函数实现
void RedBlackTree::buildFromList(const std::vector<int>& values) {
    for (int val : values) {
        insert(val);
    }
}

// 简单析构函数（实际项目中应遍历删除所有节点）
RedBlackTree::~RedBlackTree() {
    // 还需要实现完整的清理逻辑，这里为了示例简单暂时省略
    delete TNULL;
}

// 前序遍历辅助函数
void RedBlackTree::preOrderHelper(RBNode *node) {
    if (node != TNULL) {
        std::cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

// 中序遍历辅助函数
void RedBlackTree::inOrderHelper(RBNode *node) {
    if (node != TNULL) {
        inOrderHelper(node->left);
        std::cout << node->data << " ";
        inOrderHelper(node->right);
    }
}

RBNode* RedBlackTree::searchTreeHelper(RBNode* node, int key) {
    if (node == TNULL || key == node->data) {
        return node;
    }

    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}

// 修复删除操作后的红黑树性质
void RedBlackTree::fixDelete(RBNode* x) {
    RBNode* s;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == BLACK && s->left->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RedBlackTree::rbTransplant(RBNode* u, RBNode* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RedBlackTree::deleteNodeHelper(RBNode* node, int key) {
    RBNode* z = TNULL;
    RBNode* x;
    RBNode* y;
    RBNode* temp = node;

    while (temp != TNULL) {
        if (temp->data == key) {
            z = temp;
        }

        if (temp->data <= key) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }

    if (z == TNULL) {
        std::cout << "Key not found in the tree" << std::endl;
        return;
    }

    y = z;
    Color yOriginalColor = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == BLACK) {
        fixDelete(x);
    }
}

// 修复插入操作后的红黑树性质
void RedBlackTree::fixInsert(RBNode* k) {
    RBNode* u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;

            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = BLACK;
}

void RedBlackTree::printHelper(RBNode* root, std::string indent, bool last) {
    if (root != TNULL) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }

        std::string sColor = (root->color == RED) ? "RED" : "BLACK";
        std::cout << root->data << "(" << sColor << ")" << std::endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}

// 公共接口实现
void RedBlackTree::preOrder() {
    preOrderHelper(this->root);
}

void RedBlackTree::inOrder() {
    inOrderHelper(this->root);
}

RBNode* RedBlackTree::searchTree(int k) {
    return searchTreeHelper(this->root, k);
}

RBNode* RedBlackTree::minimum(RBNode *node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

RBNode* RedBlackTree::maximum(RBNode *node) {
    while (node->right != TNULL) {
        node = node->right;
    }
    return node;
}

RBNode* RedBlackTree::successor(RBNode *x) {
    if (x->right != TNULL) {
        while (x->left != TNULL) {
            x = x->left;
        }
        return x;
    }

    RBNode* y = x->parent;
    while (y != TNULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

RBNode* RedBlackTree::predecessor(RBNode *x) {
    if (x->left != TNULL) {
        while (x->right != TNULL) {
            x = x->right;
        }
        return x;
    }

    RBNode* y = x->parent;
    while (y != TNULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

void RedBlackTree::leftRotate(RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(RBNode *x) {
    RBNode *y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RedBlackTree::insert(int key) {
    RBNode* node = new RBNode(key);
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED;

    RBNode* y = nullptr;
    RBNode* x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    fixInsert(node);
}

RBNode* RedBlackTree::getRoot() {
    return this->root;
}

void RedBlackTree::deleteNode(int data) {
    deleteNodeHelper(this->root, data);
}

void RedBlackTree::prettyPrint() {
    if (root) {
        printHelper(this->root, "", true);
    }
}

// 演示函数的实现
void runRedBlackTreeDemo() {
    std::cout << "\n=== 红黑树演示开始 ===" << std::endl;

    // 方式 1：使用初始化列表直接一次性建立树
    std::cout << "1. 使用初始化列表 {55, 40, 65, 60, 75, 57} 直接建树..." << std::endl;
    RedBlackTree bst = {55, 40, 65, 60, 75, 57};

    // 或者方式 2：使用 vector 批量插入
    // std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    // bst.buildFromList(data);

    std::cout << "\n当前树结构 (R---- 代表右子树, L---- 代表左子树):" << std::endl;
    bst.prettyPrint();

    std::cout << "\n中序遍历: ";
    bst.inOrder();
    std::cout << std::endl;

    std::cout << "\n前序遍历: ";
    bst.preOrder();
    std::cout << std::endl;

    std::cout << "\n删除节点 40" << std::endl;
    bst.deleteNode(40);
    bst.prettyPrint();
    
    std::cout << "\n删除节点 55 (原根节点)" << std::endl;
    bst.deleteNode(55);
    bst.prettyPrint();
    
    std::cout << "=== 红黑树演示结束 ===" << std::endl;
}
