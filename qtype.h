#ifndef _QTYPE_H  // header guard
#define _QTYPE_H
// key ���� �ִ� 10000000�̹Ƿ� dequeue ���� enqueue�� �ִٴ� �����Ͽ� �ִ� �������� �迭�� ����
#define MAX_HEAP_SIZE 10000000
#include <mutex>
// ==========�� ������ ���� ����==========

typedef unsigned int Key;  // ���� Ŭ���� ���� �켱����
typedef void* Value;

typedef struct {
    Key key;
    Value value;
} Item;

typedef struct {
    bool success;   // true: ����, false: ����
    Item item;
    // �ʵ� �߰� ����
} Reply;

typedef struct node_t {
    Item item;
    struct node_t* next;
    // �ʵ� �߰� ����
} Node;

//======������ safe queue ������ ���� ���Ḯ��Ʈ ��� heap�迭 ����ϱ�� ����)
typedef struct {
    Node* head, *tail;
    Item heap[MAX_HEAP_SIZE];
    int size;
    std::mutex lock;
    // �ʵ� �߰� ����
} Queue;

// ���� �����Ӱ� �߰�/����: ���ο� �ڷ��� ���� ��

#endif
#pragma once
