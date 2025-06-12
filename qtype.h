#ifndef _QTYPE_H  // header guard
#define _QTYPE_H
// key 값이 최대 10000000이므로 dequeue 없이 enqueue만 있다는 가정하에 최대 사이즈의 배열로 선언
#define MAX_HEAP_SIZE 2000000
#include <mutex>
// ==========이 파일은 수정 가능==========

// queue 크기가 커질수록 key 값을 검사하는 비용이 커지므로 key 값 검사를 HASH로 구현
#define HASH_SIZE (1 << 22)

typedef unsigned int Key;  // 값이 클수록 높은 우선순위
typedef void* Value;

typedef struct {
    Key key;
    Value value;
    int value_size; // void 포인터의 값을 깊은복사 하기위한 바이트 사이즈
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

// ===== 해시맵 구조체 정의 (Open Addressing, Linear Probing) =====
typedef struct {
    Key key;
    int index;  // heap 배열 상의 인덱스
    bool valid;
} HashEntry;


//======스레드 safe queue 구현을 위해 연결리스트 대신 heap배열 사용하기로 결정)
typedef struct {
    Node* head, *tail;
    Item* heap;
    int size;
    std::mutex lock;
    HashEntry hashTable[HASH_SIZE];// 키 → 힙 배열 인덱스 매핑
    // 필드 추가 가능
} Queue;

// 이후 자유롭게 추가/수정: 새로운 자료형 정의 등

#endif

