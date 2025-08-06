#ifndef POSTFIX_H
#define POSTFIX_H
// 수식에 사용되는 연산자들 정의
typedef enum {
    LPAREN, RPAREN, // ( )
    PLUS, MINUS, MULTIPLY, DIVIDE, MODULUS,
    EOS, OPERAND, NUMBER, DOT // 연산자인지 숫자인지 .인지
}OPERATOR;
// 스택에 있을 때 연산자들의 우선순위를 결정
// ( ) + - * / % 의 우선순위 (클수록 우선순위 높음)
static int isp[] = {0, 10, 1, 1, 2, 2, 3};
OPERATOR get_operator_priority(char operator);
int check_token(char token);
char* change_postfix(char expression[]);
void print_postfix(char* postfix);
void postfix_main();
#endif //POSTFIX_H
