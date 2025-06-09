#ifndef _QTYPE_H  // header guard
#define _QTYPE_H
// key 값이 최대 10000000이므로 dequeue 없이 enqueue만 있다는 가정하에 최대 사이즈의 배열로 선언
#define MAX_HEAP_SIZE 10000000
#include <mutex>
// ==========이 파일은 수정 가능==========

typedef unsigned int Key;  // 값이 클수록 높은 우선순위
typedef void* Value;

typedef struct {
    Key key;
    Value value;
} Item;

typedef struct {
    bool success;   // true: 성공, false: 실패
    Item item;
    // 필드 추가 가능
} Reply;

typedef struct node_t {
    Item item;
    struct node_t* next;
    // 필드 추가 가능
} Node;

//======스레드 safe queue 구현을 위해 연결리스트 대신 heap배열 사용하기로 결정)
typedef struct {
    Node* head, *tail;
    Item heap[MAX_HEAP_SIZE];
    int size;
    std::mutex lock;
    // 필드 추가 가능
} Queue;

// 이후 자유롭게 추가/수정: 새로운 자료형 정의 등

#endif
#pragma once
