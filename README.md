# 이름: 오준수 
# (학번 뒷자리: 153)

> ... 작업하던 파일을 중간에 한 번 날려서 급하게 6/10부터 다시 시작하였습니다..!
---

# 진행 : enqueue, dequeue, range 함수 모두 구현 완료 
# 사용한 자료구조 : Binary Heap으로 queue 구현 및 hash table로 key값 검사


---

##  1. 6/10일

### (1) **heap size 정의..**
- heap size 정의 및 큐 구조체에 힙 배열 및 뮤텍스 변수 추가  
  (검색 및 수업에서 들었던 내용을 바탕으로 연결리스트 대신 binary heap 기반 MAX HEAP으로 구현하기로 결정)
- heap size에 대한 고민이 있었는데  
  **일단 key값이 10,000,000까지 있으니 10,000,000으로 하기로 결정**

### (2) **queue init 함수 작성**
- 일단 head랑 tail은 사용하지 않지만 null 초기화는 했고  
  queue의 size, heap 메모리 동적 할당 기능 추가

### (3) **release 함수 추가**

### (4) **swap 함수 + heapify 함수 구현**
- swap 함수를 만들고, 삽입된 요소를 끌어올리며 정렬하는 `heapify_up` 함수 구현  
  (부모 노드와 비교하며 swap하는 방식으로 구현)
- 루트에서 제거된 후 아래로 내려가면서 정렬하는 `heapify_down` 구현  
  (재귀 반복으로 자식노드와 비교하며 swap)

### (5) **enqueue, dequeue 뼈대 작성**
- `enqueue`: 힙의 max size와 비교하여 가득 차지 않았으면 삽입 후 heapify_up, 사이즈 증가, 리턴
- `dequeue`: heap이 비었으면 바로 리턴하고 반환할 아이템을 reply에 저장  
  후 마지막 요소를 루트로 옮기고 size-- 후 heapify_down 후 리턴하도록 구현
- **깊은 복사는 나중에 구현할 계획**

---

##  2. 6/11일

### (1) **unordered_map 기반 해시테이블 작성**
- `enqueue` 시 key값이 같으면 덮어씌운다.  
  → key값이 겹치는지 확인해야 하며 선형 검사 시 처리율이 매우 떨어지는 걸 확인  
  → **C++ STL 해시 테이블(`unordered_map`) 사용 결정**
- Queue 구조체에 Key값과 힙 배열의 인덱스를 매핑하는 해시테이블 생성
- `heapify_up`, `heapify_down` 함수에 swap 전 인덱스 맵 업데이트 코드 추가

### (2) **enqueue 함수에 key값 검사 + 깊은 복사 추가**
- key값이 존재하면 값만 교체하는 방식
- 깊은 복사를 위해 `value_size`에 맞는 새로운 void*에 메모리를 동적 할당하고  
  `memcpy`로 복사해서 heap에 삽입

### (3) **dequeue 함수에 인덱스 맵 제거 코드 추가**

---

##  3. 6/12일

### (1) **unordered_map 제거, 직접 해시 테이블 구현**
- 과제 조건 재확인 결과 unordered_map 사용은 부적절하다고 판단
- 직접 해시맵 구조체인 `HashEntry` 추가  
  (구성: `키값`, `힙배열 index`, `valid` 불리언 값)

### (2) **해시테이블 구현 (선형 탐사 기반 충돌 해결)**
- 해시함수: `key % HASH_SIZE`  
  (해시 함수에 효과적인 모듈로 연산 이용)
- `hash_find`: 해시테이블에서 key값에 해당하는 인덱스를 찾아서  
  그 위치에 이미 저장된 key가 있는지 확인 후 있으면 다음칸으로 이동하는 방식
- `hash_insert`: `hash_find` 함수로 빈 해시의 인덱스를 찾아서  
  key 및 힙 인덱스 삽입 및 `valid = true`
- `hash_erase`: `hash_find` 함수로 지우고 싶은 key값의 해시 인덱스를 확인 후 `valid = false`

### (3) **enqueue, dequeue 함수 수정**
- `unordered_map` 사용하던 부분을 직접 구현한 `hash`로 대체

### (4) **range 함수 구현**
- start, end로 들어온 값을 힙의 각 key값과 비교하여  
  조건에 맞는 항목만 새로운 queue에 넣어서 반환

### (5) **MAX_HEAP_SIZE 및 HASH_SIZE 크기 조정**
- 기존에 1천만은 너무 커서  
  → **힙사이즈는 2백만, 해시사이즈는 약 4백만** 크기로 수정  
  → 해시 충돌 최소화 목적
