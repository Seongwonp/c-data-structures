#include "sort.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 정렬된 배열을 출력
void print_arr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//// 버블 정렬
void bubble_sort(int *arr, int size) {
    // size만큼 round를 진행한다
    for (int i = 0; i < size; i++) {
        bool changed = false;
        // 배열안에 있는 모든 요소를 순회하며, 교환작업을 진행한다
        for (int j = 0; j < size - i - 1; j++) {
            // 뒤에있는 요소가 더 작으면 교환해야한다
            if (arr[j] > arr[j + 1]) {
                // 두 수를 교환한다
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                changed = true;
            }
        }
        // 한번이라도 교환작업이 이루어지지않았다면 모든 round하지않고 바로 끝낸다
        if (!changed) {
            return;
        }
    }
}

//// 선택 정렬
void selection_sort(int *arr, int size) {
    // 전체 배열에서 라운드를 순회
    for (int i = 0; i < size - 1; i++) {
        int min = i; // 현재 찾은 최소값
        // 남은 부분중에서 최소값을 찾는다 (min: 찾은 최소값의 위치)
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        // i의 위치값과 min 위치값을 서로 교환한다
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

// 삽입정렬
void insertion_sort(int arr[], int size) {
    // 정렬된 배열이 될 새 배열
    int newArr[size];
    // 원래 있는 배열과 똑같이 생성
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }

    int j;
    for (int i = 0; i < size; i++) {
        // 정렬 대상 데이터(삽입대상)
        int insertData = newArr[i];
        // 현재 삽입대상 앞부터 거꾸로 버블정렬
        for (j = i - 1; j >= 0; j--) {
            // 삽입 대상 위치로 갈때까지 교환
            if (newArr[j] > insertData) {
                newArr[j + 1] = newArr[j];
            }else {
                // 정렬 위치로 왔다! 끝!
                break;
            }
        }
        // 맨처음 데이터는 그 자리로 정렬이 되어있는 상태임
        newArr[j + 1] = insertData;
    }
    // 정렬된 새로운 배열을 출력
    print_arr(newArr, size);
}

// 병합정렬
// 합치기
void merge(int arr[], int left, int mid, int right) {
    // 병합을 위해 새로운 배열을 정의 (정렬한 결과를 잠깐 저장)
    int* sortArr = (int*)calloc(right + 1, sizeof(int));
    int fIndex = left;
    int sIndex = left;
    int rIndex = mid + 1;
    // 왼쪽 혹은 오른쪽 그룹의 데이터를 다 넣어줄 때까지 반복
    // 무조건 한쪽 그룹이 먼저 다 없어진다!
    while (fIndex <= mid && rIndex <= right) {
        if (arr[fIndex] <= arr[rIndex]) {
            sortArr[sIndex] = arr[fIndex++];
        }
        else {
            sortArr[sIndex] = arr[rIndex++];
        }
        sIndex++;
    }
    // 왼쪽 그룹이 남았는가? 오른쪽 그룹이 남았는가?
    // 오른쪽 그룹이 남았다! => 오른쪽 그룹의 남은 값들을 전부 새로운 배열에 추가
    if (fIndex > mid) {
        for (int i = rIndex; i <= right; i++) {
            sortArr[sIndex++] = arr[i];
        }
    }
    // 왼쪽 그룹이 남았다 => 왼쪽 그룹의 남은 값들을 전부 새로운 배열에 추가
    else{
        for (int i = fIndex; i <= mid; i++) {
            sortArr[sIndex++] = arr[i];
        }
    }
    // 여기까지 왔다면 배열이 전부 병합되어 있는 상태!
    // 정렬했던 데이터들을 기존 배열에서 잘라서 온 그 부분에 다시 순서대로 넣음
    for (int i = left; i <= right; i++) {
        arr[i] = sortArr[i]; // 정렬 데이터를 기존 배열에 설정
    }
    free(sortArr); // 정렬을 위해 만들었던 배열은 할일을 다 했으므로 해제
}
// 나누기
void divide(int arr[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2; // 중간위치를 구한다
        // 더 이상 나눠지지 않을 때까지 재귀로 반으로 계속 나눔
        divide(arr, left, mid); // 왼쪽 부분을 가져감
        divide(arr, mid + 1, right); // 오른쪽 부분을 가져감
        merge(arr, left, mid, right);
    }
}
/// 병합정렬 (나누기 + 합치기)
void merge_sort(int arr[], int size) {
    divide(arr, 0, size - 1);
}
/////////
// 큰것과 작은것의 위치를 변경한다
void swap(int arr[], int low, int high) {
    int temp = arr[low];
    arr[low] = arr[high];
    arr[high] = temp;
}

int create_partition(int arr[], int left, int right) {
    int pivot = arr[left]; // 피봇을 결정 (현재 부분배열에서 가장 왼쪽에 있는 요소로)
    int low = left + 1;
    int high = right;

    while (low <= high) {
        // 피봇보다 큰 값이 나올 때까지 low를 오른쪽으로 이동
        while (pivot > arr[low]) {
            low++;
        }
        // 피봇보다 작은 값이 나올때까지 high를 왼쪽으로 이동
        while (pivot < arr[high]) {
            high--;
        }
        // low와 high 위치 값 두 개를 교환
        if (low <= high) {
            swap(arr, low, high);
        }
    }
    // 위 while이 끝났을 때는 low와 high가 교차되는 시점을 기준으로
    // 교차되는 그 index 왼쪽에는 pivot보다 작은값들, 오른쪽에는 pivot보다 큰 값들만 남아있다
    // 피벗과 high의 위치를 교환 (high의 위치는 pivot보다 작은 값들 중 제일 오른쪽 값)
    swap(arr, left, high);
    // pivot은 정렬이 끝났다는 것이다. 다음 파티션의 기준이 된다
    return high;
}

void select_pivot_and_sort(int arr[], int left, int right) {
    // 왼쪽 index가 오른쪽 index 보다 작다면
    if (left <= right) {
        // 피봇을 선택한다
        int pivot = create_partition(arr, left, right);
        // 피봇의 왼쪽 부분에서 다시 피봇을 선택하고 정렬한다
        select_pivot_and_sort(arr, left, pivot - 1);
        // 피봇의 오른쪽 부분에서 다시 피봇을 선택하고 정렬한다
        select_pivot_and_sort(arr, pivot + 1, right);
    }
}

void quick_sort(int arr[], int left, int size) {
    select_pivot_and_sort(arr, 0, size - 1);
}




void main() {
    int arr[] = {5, 9, 3, 1, 2, 8, 4, 7, 6};
    // bubble_sort(arr, 9);
    // selection_sort(arr, 9);
    // insertion_sort(arr, 9);
    // print_arr(arr, 9);
    // merge_sort(arr, 9);
    // print_arr(arr, 9);
    quick_sort(arr, 0, 9);
    print_arr(arr, 9);

}