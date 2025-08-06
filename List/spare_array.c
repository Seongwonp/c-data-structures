#include <stdio.h>

typedef struct {
    int col; // 실제 데이터가 들어가는 열 번호
    int row; // 실제 데이터가 들어가는 행 번호
    int value; // 위 (행/열) 번호에 들어가는 실제 데이터
}SPARE_DATA;

void create_spare_array() {
    SPARE_DATA data1;
    data1.row = 0;
    data1.col = 0;
    data1.value = 15;

    SPARE_DATA data2;
    data2.row = 0;
    data2.col = 3;
    data2.value = 22;

    SPARE_DATA data3;
    data3.row = 0;
    data3.col = 5;
    data3.value = -15;

    SPARE_DATA spareArray[] =  {data1, data2, data3};
    for (int i = 0; i < 3; i++) {
        int row = spareArray[i].row;
        int col = spareArray[i].col;
        if (row == 0 && col == 3) {
            int value = spareArray[i].value;
            printf("%d %d %d", row, col, value);
            break;
        }
    }
}

void spare_array_main() {
    create_spare_array();
}




