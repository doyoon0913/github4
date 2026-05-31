# 📌 포인터 복습: 선택 정렬 & 동적 할당 프로그램 정리

이 파일은 C 언어의 핵심인 **포인터(Pointer)**, **동적 메모리 할당(`malloc`, `free`)**, 그리고 **선택 정렬(Selection Sort)** 개념을 복습하기 위해 작성되었습니다.

---

## 💻 소스 코드 및 라인별 상세 분석

```c
#include <stdio.h>
#include <stdlib.h> // malloc과 free 함수를 사용하기 위한 헤더 파일

/* * 1. swap 함수: Call by Reference (주소에 의한 호출)
 * - 두 변수의 '값'이 아니라 '메모리 주소'를 포인터(*a, *b)로 전달받음
 * - 함수 내부에서 원본 데이터의 값을 직접 변경하기 위함
 */
void swap(int *a, int *b) {
    int temp = *a;  // temp에 a가 가리키는 주소의 실제 값을 임시 보관
    *a = *b;        // a가 가리키는 주소 공간에 b가 가리키는 주소의 값을 덮어씀
    *b = temp;      // b가 가리키는 주소 공간에 임시 보관했던 기존 a의 값을 대입
}

/* * 2. min 함수: 배열 포인터 탐색
 * - int *list: main 함수에서 동적 할당한 배열의 시작 주소를 포인터로 받음
 * - start부터 n-1까지 탐색하며 가장 작은 값이 들어있는 '방 번호(인덱스)'를 찾음
 */
int min(int *list, int start, int n) {
    int min_idx = start; // 우선 탐색을 시작할 인덱스를 최솟값 위치로 가정
    
    for (int i = start + 1; i < n; i++) {
        // list[i]는 *(list + i)와 동일한 포인터 연산 표현식
        if (list[i] < list[min_idx]) {
            min_idx = i; // 더 작은 값을 찾으면 최솟값 인덱스를 현재 위치(i)로 갱신
        }
    }
    return min_idx; // 찾은 최솟값의 인덱스(방 번호)를 반환
}

/* * 3. select_sort 함수: 선택 정렬 구현
 * - 배열의 시작 주소(list)와 요소의 개수(n)를 매개변수로 받음
 */
void select_sort(int *list, int n) {
    for (int i = 0; i < n - 1; i++) {
        // 현재 위치(i)부터 끝까지 중 가장 작은 값의 인덱스를 찾아옴
        int min_idx = min(list, i, n);
        
        // ⭐️ 중요: swap 함수에 '실제 값이 들어있는 메모리 주소'(&)를 넘겨줌
        // list[i]의 주소(&list[i])와 list[min_idx]의 주소(&list[min_idx])를 전달
        swap(&list[i], &list[min_idx]);
    }
}

int main() {
    int n;
    scanf("%d", &n); // 정렬할 데이터의 개수 입력
    
    /* * ⭐️ 4. 동적 메모리 할당 (malloc)
     * - 정수형 크기(sizeof(int))에 n을 곱한 만큼의 바이트를 Heap 영역에 할당
     * - malloc은 할당된 공간의 시작 주소를 반환하므로 포인터 변수 *list에 저장
     * - 이제 list는 일반 배열처럼 list[0], list[1]... 형태로 접근 가능
     */
    int *list = (int *)malloc(sizeof(int) * n);
    
    // 할당받은 동적 배열 공간에 포인터 연산(인덱스)을 활용해 값 입력받기
    for (int i = 0; i < n; i++) {
        scanf("%d", &list[i]); // &list[i]는 각 배열 요소의 메모리 주소를 의미
    }
    
    // 배열의 첫 번째 요소 주소(list)와 크기(n)를 전달하여 정렬 수행
    select_sort(list, n);
    
    // 정렬이 완료된 데이터 출력
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    
    /* * ⭐️ 5. 동적 메모리 반납 (free)
     * - malloc으로 Heap 영역에 빌렸던 메모리는 프로그램 종료 전 반드시 반납해야 함
     * - 이를 생략하면 메모리 누수(Memory Leak)가 발생함
     */
    free(list);

    return 0;
}