학번 3개 뒷자리 : 153
이름 : 오준수

... 작업하던 파일을 중간에 한 번 날려서 급하기 6/10부터 다시 시작하였습니다..!
1. 6/10일
   
   (1) heap size 정의..
   - heap size 정의 및 큐 구조체에 힙 배열 및 뮤텍스 변수 추가(검색 및 수업에서 들었던 내용을 바탕으로 연결리스트 대신 binary heap 기반 MAX HEAP으로 구현하기로 결정)
   - heap size에 대한 고민이 있었는데 일단 key값이 10,000,000까지 있으니 10,000,000으로 하기로 결정
  
   (2) queue init 함수 작성
 - 일단 head랑 tail은 사용하지 않지만 null 초기화는 했고 queue의 size, heap 메모리 동적 할당 기능 추가

   (3) release 함수 추가

   (4) swap 함수를 만들고 삽입된 요소를 끌어올리며 정렬하는 heapify_up 함수 구현(부모 노드와 비교하며 swap하는 방식으로 구현) 및 루트에서 제거된 후 아래로 내려가면서 정렬하는 heapify down(재귀 반복으로 자식노드와 비교하며 swap)구현

   (5) enqueue, dequeue 뼈대 작성
   - enqueue는 힙의 max size와 비교하여 가득 차지 않았으면 삽입 후 heapify_up, 사이즈 증가, 리턴
   - dequeue는 heap이 비었으면 바로 리턴하고 반환할 아이템을 reply에 저장한 후 마지막 요소를 루트로 옮기고 size-- 후 heapify_down후 리턴하도록 구현
   - 깊은 복사는 나중에 구현할 계획
  
  
