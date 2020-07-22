#include <stdio.h>

#define LINE_SIZE 100
#define INT 1
#define CHAR 0

//트리 타입 정의
typedef union{ //공용체를 사용한 data표현
	int operand;
	char operator;
}element;
typedef struct node* nodeptr;
typedef struct node{
	int flag;
	element data;
	nodeptr left, right;
}node;

typedef struct stack_type { //스택 타입 정의 : 배열로 표현
	char stack[LINE_SIZE];
	int top;
}stack_type;
typedef stack_type* stack_type_ptr;

//수식트리 연산용 스택 타입 정의
typedef struct stack_type_forTree { //스택 타입 정의 : 배열로 표현
	nodeptr stack[LINE_SIZE];
	int top;
}stack_type_forTree;
typedef stack_type_forTree* stack_type_ptr_forTree;

//노드 생성 함수
nodeptr create_node(int flag);

//스택 타입 연산 함수
void init(stack_type_ptr);
void push(stack_type_ptr, char item);
char pop(stack_type_ptr*);
int is_empty(stack_type);
int is_full(stack_type);
char peek(stack_type);

//수식트리 연산용 스택 타입 연산 함수
void init_forTree(stack_type_ptr_forTree);
void push_forTree(stack_type_ptr_forTree, nodeptr item);
nodeptr pop_forTree(stack_type_ptr_forTree*);
int is_empty_forTree(stack_type_forTree);
int is_full_forTree(stack_type_forTree);
nodeptr peek_forTree(stack_type_forTree);

//연산자 우선순위 반환 함수
int PIS(char token);
int PIE(char token);

int menu();
//스택 식 함수
void get_exp(char exp[]);
void postfix(char exp[], char postExp[], stack_type_ptr s_ptr);
void display(char exp[], char postExp[], int result);

//트리 식 함수
nodeptr cons(char postExp[]);
int eval(nodeptr T);
int calc(op, opnd1, opnd2);

int main(void)
{
	int select, result; //사용자가 원할 때 까지 반복하는 제어변수 select, 계산결과 저장 변수 result 선언
	char exp[LINE_SIZE], postExp[LINE_SIZE]; //중위 식, 후위 식 문자열 선언
	nodeptr T = NULL;
	stack_type s; // 스택 선언
	stack_type_ptr s_ptr = &s; //스택 포인터 선언

	init(s_ptr); //스택 초기화

	do{
		select = menu();

		if (select == 1){
			get_exp(exp); //중위 식 입력
			postfix(exp, postExp, s_ptr); //후위 식으로 변환
			T = cons(postExp); //후위 식으로부터 수식 트리 구성
			result = eval(T); //수식트리 평가
			display(exp, postExp, result); //중위 식, 후위 식 및 계산 결과 출력
		}
	} while (select == 1);

	printf("프로그램을 종료합니다.");

	getch();
	return 0;
}

nodeptr cons(char postExp[]){

	//트리 변환용 스택 선언 및 초기화
	stack_type_forTree tmp;
	stack_type_ptr_forTree tmp_ptr = &tmp;
	init_forTree(tmp_ptr);

	int i = 0; //후위 식 인덱스 변수
	char token; //토큰 저장 변수

	while (postExp[i] != NULL){

		token = postExp[i];
		if (token >= '0' && token <= '9'){
			//잎노드 구성
			nodeptr new = create_node(INT);
			new->data.operand = token - 48;
			//스택에 노드 저장
			push_forTree(tmp_ptr, new);
		}

		else{
			//연산자 노드 구성
			nodeptr new = create_node(CHAR);
			new->data.operator = token;
			//연산자 노드와 2개의 스택에서 꺼내온 2개의 서브트리를 트리로 구성
			new->right = pop_forTree(&tmp_ptr);
			new->left = pop_forTree(&tmp_ptr);
			//구성된 트리를 스택에 저장
			push_forTree(tmp_ptr, new);
		}
		i++; //postExp의 인덱스 번호 증가
	}

	return pop_forTree(&tmp_ptr); //결과의 수식트리 변환
}

nodeptr create_node(int flag)
{
	nodeptr new = (nodeptr)malloc(sizeof(struct node));

	if (flag == INT)
		new->flag = INT;
	else if (flag == CHAR)
		new->flag = CHAR;

	new->left = NULL;
	new->right = NULL;
	return new;
}

int menu()
{
	int select;
	printf("식을 입력하시려면 1을 입력하세요. :");
	scanf("%d", &select);
	getchar(); //버퍼 제거

	return select;
}

void get_exp(char exp[])
{
	printf("중위 식을 입력하세요 : ");
	gets(exp);
}

void postfix(char exp[], char postExp[], stack_type_ptr s_ptr)
{
	int i = 0, k = 0;
	char token;

	while (exp[i] != NULL) {

		token = exp[i];

		if (token >= '0' && token <= '9') { //피연산자일때
			postExp[k] = token;
			k++;
		}

		else if (token == '*' || token == '/' || token == '%' || token == '+' || token == '-' || token == '(') {
			while (is_empty(*s_ptr) == 0 && PIS(peek(*s_ptr)) >= PIE(token)) {  //스택의 연산자가 식의 연산자보다 크거나 같을 때
				postExp[k] = pop(&s_ptr);
				k++;
			}
			push(s_ptr, token);
		}

		else if (token == ')') {//괄호를 만나면
			while ((token = pop(&s_ptr)) != '(') {
				postExp[k] = token;
				k++;
			}
		}
		i++;
	}

	while (s_ptr->top >= 0) {
		postExp[k] = pop(&s_ptr);
		k++;
	}
	postExp[k] = NULL;
}

int eval(nodeptr T)
{
	int opnd1, opnd2;
	char op;

	if (T == NULL)
		return NULL;
	
	if (T->left == NULL && T->right == NULL) // T가 잎노드 일 때
		return T->data.operand;

	else{ //T가 비단말노드 일 때
		opnd1 = eval(T->left); //왼쪽 서브트리 계산
		opnd2 = eval(T->right); //오른쪽 서브트리 계산
		op = T->data.operator; //루트
		return  calc(op, opnd1, opnd2);//최종 값 반환
	}
}

int calc(op, opnd1, opnd2){

	switch (op){
	case '+':
		return opnd1 + opnd2;
	case '-':
		return opnd1 - opnd2;
	case '*':
		return opnd1 * opnd2;
	case '/':
		return opnd1 / opnd2;
	case '%':
		return opnd1 % opnd2;
	default :
		return NULL;
	}
}

void display(char exp[], char postExp[], int result)
{
	printf("입력 한 중위 식 : %s\n", exp);
	printf("입력 한 후위 식 : %s\n", postExp);
	printf("계산 결과 : %d\n", result);
}

void init(stack_type_ptr s_ptr)
{
	s_ptr->top = -1;
}

void init_forTree(stack_type_ptr_forTree s_ptr)
{
	s_ptr->top = -1;
}

void push(stack_type_ptr s_ptr, char item)
{
	if (is_full(*s_ptr) == 0) {
		s_ptr->top++;
		s_ptr->stack[s_ptr->top] = item;
	}
	else {
		printf("스택이 꽉 차있습니다.");
	}
}

void push_forTree(stack_type_ptr_forTree s_ptr , nodeptr item)
{
	if (is_full_forTree(*s_ptr) == 0) {
		s_ptr->top++;
		s_ptr->stack[s_ptr->top] = item;
	}
	else {
		printf("스택이 꽉 차있습니다.");
	}
}

char pop(stack_type_ptr* s_ptr)
{
	if (is_empty(**s_ptr) == 0) {
		char returner = ((*s_ptr)->stack[(*s_ptr)->top]);
		(*s_ptr)->top--;
		return returner;
	}
	else {
		printf("스택이 비어있습니다.");
		return 0;
	}
}

nodeptr pop_forTree(stack_type_ptr_forTree* s_ptr)
{
	if (is_empty_forTree(**s_ptr) == 0) {
		nodeptr returner = ((*s_ptr)->stack[(*s_ptr)->top]);
		(*s_ptr)->top--;
		return returner;
	}
	else {
		printf("스택이 비어있습니다.");
		return 0;
	}
}

int is_empty(stack_type s)
{
	if (s.top < 0)
		return 1;
	else return 0;
}

int is_empty_forTree(stack_type_forTree s)
{
	if (s.top < 0)
		return 1;
	else return 0;
}

int is_full(stack_type s)
{
	if (s.top == LINE_SIZE - 1)
		return 1;
	else return 0;
}

int is_full_forTree(stack_type_forTree s)
{
	if (s.top == LINE_SIZE - 1)
		return 1;
	else return 0;
}

char peek(stack_type s) //스택의 맨 위의 값 반환
{
	return s.stack[s.top];
}

nodeptr peek_forTree(stack_type_forTree s) //스택의 맨 위의 값 반환
{
	return s.stack[s.top];
}

int PIS(char token) //스택내에서 연산자 순위 반환
{
	if (token == '*' || token == '/' || token == '%')
		return 2;
	else if (token == '+' || token == '-')
		return 1;
	else return 0;
}

int PIE(char token) //식 내에서 연산자 순위 반환
{
	if (token == '*' || token == '/' || token == '%')
		return 2;
	else if (token == '+' || token == '-')
		return 1;
	else return 3;
}
