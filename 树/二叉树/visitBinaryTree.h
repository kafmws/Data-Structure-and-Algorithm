#pragma once

#include"pch.h"

void preOrder(BinaryTree * root);

void midOrder(BinaryTree * root);

void postOrder(BinaryTree * root);

void levelOrderRe(Queue * q);

void levelOrder(Queue * q);

void levelOrderInQueue(BinaryTree * root);

void preOrderInStackRe(Stack * s);

void preOrderInStackNoRe(Stack * s);

void preOrderInStack(BinaryTree * root);

void midOrderInStackRe(Stack * s);

void midOrderInStackNoRe(Stack * s);

void midOrderInStack(BinaryTree * root);

void postOrderInStackRe(Stack * s);

void postOrderInStackNoRe(Stack * s);

void postOrderInStack(BinaryTree * root);

void drawBinaryTree(BinaryTree * root, int height);

int cntLeaves(BinaryTree * root, int objLevel);

int measureHeight(BinaryTree * root, int curH);

