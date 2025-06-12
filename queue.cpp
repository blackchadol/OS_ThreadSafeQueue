#include <iostream>
#include "queue.h"

// 10,000,000개 배열을 시작부터 선언하면 메모리를 너무 크게 잡아먹을 가능성 있으므로 나중에 수정.
Queue* init(void) {
	Queue* q = new Queue;
	q->size = 0;
	q->heap = (Item*)malloc(sizeof(Item) * MAX_HEAP_SIZE);
	q->head = nullptr;
	q->tail = nullptr;
	// 해시 테이블 초기화
	for (int i = 0; i < HASH_SIZE; ++i) {
		q->hashTable[i].valid = false;   // 사용 안됨 표시
		q->hashTable[i].key = 0;         // 의미 없는 초기값
		q->hashTable[i].index = -1;      // 유효하지 않은 인덱스
	}
	return q;
}


void release(Queue* queue) {
	delete[] queue->heap;
	delete queue;
	return;
}


Node* nalloc(Item item) {
	// Node 생성, item으로 초기화
	return NULL;
}


void nfree(Node* node) {
	return;
}


Node* nclone(Node* node) {
	return NULL;
}

void swap(Item& a, Item& b) {
	Item tmp = a;
	a = b;
	b = tmp;
}

int hash_func(Key key) {
	return key % HASH_SIZE;
}
int hash_find(HashEntry* table, Key key) {
	int idx = hash_func(key);
	int start = idx;
	while (table[idx].valid) {
		if (table[idx].key == key)
			return idx;
		idx = (idx + 1) % HASH_SIZE;
		if (idx == start) break;
	}
	return -1;  // not found
}

int hash_insert(HashEntry* table, Key key, int heap_idx) {
	int idx = hash_func(key);
	while (table[idx].valid) {
		if (table[idx].key == key) {
			table[idx].index = heap_idx;
			return idx;
		}
		idx = (idx + 1) % HASH_SIZE;
	}
	table[idx].key = key;
	table[idx].index = heap_idx;
	table[idx].valid = true;
	return idx;
}

void hash_erase(HashEntry* table, Key key) {
	int idx = hash_find(table, key);
	if (idx >= 0) table[idx].valid = false;
}

//===key 값이 높을 수록 우선순위가 높기 때문에 MAX_HEAP 기반 자료구조 구현====//
void heapify_up(Queue* queue, int index) {
	while (index > 0) {
		int parent = (index - 1) / 2;
		if (queue->heap[parent].key >= queue->heap[index].key) break; 

		hash_insert(queue->hashTable, queue->heap[parent].key, index);
		hash_insert(queue->hashTable, queue->heap[index].key, parent);
		
		swap(queue->heap[parent], queue->heap[index]);
		index = parent;
	}
}

void heapify_down(Queue* queue, int index) {
	int largest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	// 왼쪽 자식이 더 크면 largest 업데이트
	if (left < queue->size && queue->heap[left].key > queue->heap[largest].key)
		largest = left;

	// 오른쪽 자식이 더 크면 largest 업데이트
	if (right < queue->size && queue->heap[right].key > queue->heap[largest].key)
		largest = right;

	// largest가 바뀌었으면 교환하고 재귀 호출
	if (largest != index) {

		hash_insert(queue->hashTable, queue->heap[largest].key, index);
		hash_insert(queue->hashTable, queue->heap[index].key, largest);

		swap(queue->heap[index], queue->heap[largest]);
		heapify_down(queue, largest);  // 재귀 호출
	}
}


// 추우에 깊은 복사 및 key 값 검사 방식 추가 예정
Reply enqueue(Queue* queue, Item item) {
	Reply reply = { false, NULL };
	std::lock_guard<std::mutex> lg(queue->lock);

	int hidx = hash_find(queue->hashTable, item.key);
	if (hidx != -1) {
		int idx = queue->hashTable[hidx].index;
		free(queue->heap[idx].value);
		void* new_val = malloc(item.value_size);
		memcpy(new_val, item.value, item.value_size);
		queue->heap[idx].value = new_val;
		queue->heap[idx].value_size = item.value_size;
		reply.success = true;
		reply.item = queue->heap[idx];
		return reply;
	}
	if (queue->size >= MAX_HEAP_SIZE) {
		return reply;  // 힙이 가득 찼음
	}

	// 마지막 위치에 삽입
	queue->heap[queue->size] = item;
	void* new_val = malloc(item.value_size);
	memcpy(new_val, item.value, item.value_size);
	queue->heap[queue->size].value = new_val;
	queue->heap[queue->size].value_size = item.value_size;
	hash_insert(queue->hashTable, item.key, queue->size);

	// 해시에 키 추가. 
	//queue->keyIndexMap[item.key] = queue->size;
	// 힙 속성 복구
	heapify_up(queue, queue->size);

	// 크기 증가
	queue->size++;

	// 성공 리턴
	reply.success = true;
	reply.item = item;
	return reply;
}

Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };
	std::lock_guard<std::mutex> lg(queue->lock);

	if (queue->size == 0) {
		return reply;  // 큐가 비었음
	}

	// 반환할 아이템은 루트
	reply.item = queue->heap[0];
	reply.success = true;
	hash_erase(queue->hashTable, reply.item.key);
	// 마지막 요소를 루트로 옮김
	queue->heap[0] = queue->heap[queue->size - 1];

	// 크기 감소
	queue->size--;
	hash_insert(queue->hashTable, queue->heap[0].key, 0);
	// 힙 속성 복구
	heapify_down(queue, 0);

	return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
