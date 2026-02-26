#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <vector>
#include <initializer_list>

// 定义节点颜色
enum Color { RED, BLACK };

// 定义树节点结构
struct RBNode {
    int data;
    Color color;
    RBNode *left, *right, *parent;

    RBNode(int val);
};

// 红黑树类定义
class RedBlackTree {
private:
    RBNode *root;
    RBNode *TNULL; // 哨兵节点，表示空（黑色）

    // 辅助函数
    void initializeTNULL();
    void preOrderHelper(RBNode *node);
    void inOrderHelper(RBNode *node);
    RBNode* searchTreeHelper(RBNode* node, int key);
    void fixDelete(RBNode* x);
    void rbTransplant(RBNode* u, RBNode* v);
    void deleteNodeHelper(RBNode* node, int key);
    void fixInsert(RBNode* k);
    void printHelper(RBNode* root, std::string indent, bool last);

public:
    RedBlackTree();
    RedBlackTree(std::initializer_list<int> list); // 新增：支持 {1, 2, 3} 初始化
    ~RedBlackTree(); // 现在只是简单示例，析构函数可能需要完善内存清理

    // 公共接口
    void buildFromList(const std::vector<int>& values); // 新增：支持 vector 批量插入
    void preOrder();
    void inOrder();
    RBNode* searchTree(int k);
    RBNode* minimum(RBNode *node);
    RBNode* maximum(RBNode *node);
    RBNode* successor(RBNode *x);
    RBNode* predecessor(RBNode *x);
    void leftRotate(RBNode *x);
    void rightRotate(RBNode *x);
    void insert(int key);
    RBNode* getRoot();
    void deleteNode(int data);
    void prettyPrint(); // 漂亮的打印树结构
};

// 一个单独的函数用来运行红黑树演示，避免逻辑写在main中
void runRedBlackTreeDemo();

#endif
