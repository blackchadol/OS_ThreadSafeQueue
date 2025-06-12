#include <iostream>
#include "queue.h"

// 10,000,000�� �迭�� ���ۺ��� �����ϸ� �޸𸮸� �ʹ� ũ�� ��Ƹ��� ���ɼ� �����Ƿ� ���߿� ����.
Queue* init(void) {
	Queue* q = new Queue;
	q->size = 0;
	q->heap = (Item*)malloc(sizeof(Item) * MAX_HEAP_SIZE);
	q->head = nullptr;
	q->tail = nullptr;
	// �ؽ� ���̺� �ʱ�ȭ
	for (int i = 0; i < HASH_SIZE; ++i) {
		q->hashTable[i].valid = false;   // ��� �ȵ� ǥ��
		q->hashTable[i].key = 0;         // �ǹ� ���� �ʱⰪ
		q->hashTable[i].index = -1;      // ��ȿ���� ���� �ε���
	}
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

//===key ���� ���� ���� �켱������ ���� ������ MAX_HEAP ��� �ڷᱸ�� ����====//
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

	// ���� �ڽ��� �� ũ�� largest ������Ʈ
	if (left < queue->size && queue->heap[left].key > queue->heap[largest].key)
		largest = left;

	// ������ �ڽ��� �� ũ�� largest ������Ʈ
	if (right < queue->size && queue->heap[right].key > queue->heap[largest].key)
		largest = right;

	// largest�� �ٲ������ ��ȯ�ϰ� ��� ȣ��
	if (largest != index) {

		hash_insert(queue->hashTable, queue->heap[largest].key, index);
		hash_insert(queue->hashTable, queue->heap[index].key, largest);

		swap(queue->heap[index], queue->heap[largest]);
		heapify_down(queue, largest);  // ��� ȣ��
	}
}


// �߿쿡 ���� ���� �� key �� �˻� ��� �߰� ����
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
		return reply;  // ���� ���� á��
	}

	// ������ ��ġ�� ����
	queue->heap[queue->size] = item;
	void* new_val = malloc(item.value_size);
	memcpy(new_val, item.value, item.value_size);
	queue->heap[queue->size].value = new_val;
	queue->heap[queue->size].value_size = item.value_size;
	hash_insert(queue->hashTable, item.key, queue->size);

	// �ؽÿ� Ű �߰�. 
	//queue->keyIndexMap[item.key] = queue->size;
	// �� �Ӽ� ����
	heapify_up(queue, queue->size);

	// ũ�� ����
	queue->size++;

	// ���� ����
	reply.success = true;
	reply.item = item;
	return reply;
}

Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };
	std::lock_guard<std::mutex> lg(queue->lock);

	if (queue->size == 0) {
		return reply;  // ť�� �����
	}

	// ��ȯ�� �������� ��Ʈ
	reply.item = queue->heap[0];
	reply.success = true;
	hash_erase(queue->hashTable, reply.item.key);
	// ������ ��Ҹ� ��Ʈ�� �ű�
	queue->heap[0] = queue->heap[queue->size - 1];

	// ũ�� ����
	queue->size--;
	hash_insert(queue->hashTable, queue->heap[0].key, 0);
	// �� �Ӽ� ����
	heapify_down(queue, 0);

	return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
