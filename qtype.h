#ifndef _QTYPE_H  // header guard
#define _QTYPE_H
// key ���� �ִ� 10000000�̹Ƿ� dequeue ���� enqueue�� �ִٴ� �����Ͽ� �ִ� �������� �迭�� ����
#define MAX_HEAP_SIZE 2000000
#include <mutex>
// ==========�� ������ ���� ����==========

// queue ũ�Ⱑ Ŀ������ key ���� �˻��ϴ� ����� Ŀ���Ƿ� key �� �˻縦 HASH�� ����
#define HASH_SIZE (1 << 22)

typedef unsigned int Key;  // ���� Ŭ���� ���� �켱����
typedef void* Value;

typedef struct {
    Key key;
    Value value;
    int value_size; // void �������� ���� �������� �ϱ����� ����Ʈ ������
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

// ===== �ؽø� ����ü ���� (Open Addressing, Linear Probing) =====
typedef struct {
    Key key;
    int index;  // heap �迭 ���� �ε���
    bool valid;
} HashEntry;


//======������ safe queue ������ ���� ���Ḯ��Ʈ ��� heap�迭 ����ϱ�� ����)
typedef struct {
    Node* head, *tail;
    Item* heap;
    int size;
    std::mutex lock;
    HashEntry hashTable[HASH_SIZE];// Ű �� �� �迭 �ε��� ����
    // �ʵ� �߰� ����
} Queue;

// ���� �����Ӱ� �߰�/����: ���ο� �ڷ��� ���� ��

#endif

