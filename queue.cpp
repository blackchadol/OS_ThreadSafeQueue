#include <iostream>
#include "queue.h"

// 10,000,000�� �迭�� ���ۺ��� �����ϸ� �޸𸮸� �ʹ� ũ�� ��Ƹ��� ���ɼ� �����Ƿ� ���߿� ����.
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
	// Node ����, item���� �ʱ�ȭ
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

//===key ���� ���� ���� �켱������ ���� ������ MAX_HEAP ��� �ڷᱸ�� ����====//
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

	// ���� �ڽ��� �� ũ�� largest ������Ʈ
	if (left < queue->size && queue->heap[left].key > queue->heap[largest].key)
		largest = left;

	// ������ �ڽ��� �� ũ�� largest ������Ʈ
	if (right < queue->size && queue->heap[right].key > queue->heap[largest].key)
		largest = right;

	// largest�� �ٲ������ ��ȯ�ϰ� ��� ȣ��
	if (largest != index) {
		swap(queue->heap[index], queue->heap[largest]);
		heapify_down(queue, largest);  // ��� ȣ��
	}
}


// �߿쿡 ���� ���� �� key �� �˻� ��� �߰� ����
Reply enqueue(Queue* queue, Item item) {
	Reply reply = { false, NULL };

	if (queue->size >= MAX_HEAP_SIZE) {
		return reply;  // ���� ���� á��
	}

	// ������ ��ġ�� ����
	queue->heap[queue->size] = item;

	// �� �Ӽ� ����
	heapify_up(queue, queue->size);

	// ũ�� ����
	queue->size++;

	// ���� ����
	reply.success = true;
	return reply;
}

Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };

	if (queue->size == 0) {
		return reply;  // ť�� �����
	}

	// ��ȯ�� �������� ��Ʈ
	reply.item = queue->heap[0];
	reply.success = true;

	// ������ ��Ҹ� ��Ʈ�� �ű�
	queue->heap[0] = queue->heap[queue->size - 1];

	// ũ�� ����
	queue->size--;

	// �� �Ӽ� ����
	heapify_down(queue, 0);

	return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
