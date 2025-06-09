#include <iostream>
#include "queue.h"

// 10,000,000개 배열을 시작부터 선언하면 메모리를 너무 크게 잡아먹을 가능성 있으므로 나중에 수정.
Queue* init(void) {
	Queue* q = new Queue;
	q->size = 0;
	q->heap = (Item*)malloc(sizeof(Item) * MAX_HEAP_SIZE);
	q->head = nullptr;
	q->tail = nullptr;
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

//===key 값이 높을 수록 우선순위가 높기 때문에 MAX_HEAP 기반 자료구조 구현====//
void heapify_up(Queue* queue, int index) {
	while (index > 0) {
		int parent = (index - 1) / 2;
		if (queue->heap[parent].key >= queue->heap[index].key) break; 
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
		swap(queue->heap[index], queue->heap[largest]);
		heapify_down(queue, largest);  // 재귀 호출
	}
}



Reply enqueue(Queue* queue, Item item) {
	Reply reply = { false, NULL };
	return reply;
}

Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };
	return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
