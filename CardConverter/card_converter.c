#include <stdio.h>

// ���� ������ 2���� - 36������ ��� ��ȯ
// x: ��ȯ�ϰ� ���� ���� ����
// n: ��ȯ�ϰ� ���� ����
// d: ��ȯ�� ������ ���ڿ��� �����ϱ� ���� �迭
int card_converter(unsigned int x, int n, char d[]) {
    char dChar[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int digit = 0; // ���� ��ȯ�Ǵ� ������ index ����
    if (x == 0) {
        d[0] = '0';
        digit++;
    }
    while (x) { // x�� 0�� �� ������ �ݺ��Ѵ�
        // ������ ������ ���ڸ� �迭�� �����Ѵ�
        d[digit] = dChar[x % n]; // ������ ����� �ڸ��� �����Ѵ�
        digit++; // ���� �ڸ��� �̵��Ѵ�
        x /= n; // x�� ���� ������ ��ȯ�Ѵ�
    }
    return digit; // �о�� �ϴ� �ڸ����� return
}

void card_converter_main() {
    int number; // ��ȯ�� 10����
    int card; // ��ȯ�ϰ� ���� ����
    char result[512]; // ��ȯ����� �����ϴ� char �迭

    puts("======== 10���� ��� ��ȯ ���α׷� ========== ");
    printf("��ȯ�� 10������ �Է��ϼ��� >>");
    scanf("%u", &number); // 10���� �Է¹ޱ�
    printf("�� ������ ��ȯ�ұ��? >>");
    scanf("%d", &card);
    // ��ȯ�� ���ڿ� ������ ������ ��, result���� print�� �����ؾ��ϴ� ��ġ�� �޾ƿ�
    int digitStartIndex = card_converter(number, card, result);
    printf("��ȯ���: ");
    for (int i = digitStartIndex - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
}






