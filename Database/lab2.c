#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	char name[10];
	char address[100];
	int age;
}information;

void msgGetName() {
	printf("[검색을 시작합니다...]\n");
	printf(">>>방문하고자 하는 주소록 대상의 이름을 입력하세요.\n");
	printf(">이름: ");
}

void msgFail(int flag) {
	puts("");
	printf("[검색실패]\n");
	printf("============\n");
	if (flag == 1) {
		printf("주소록 방문에 실패하였습니다 > File Open Error!");
	}
	else if (flag == 3) {
		printf("주소록 방문에 실패하였습니다 > InputName Not In info.bin");
	}
	else {
		printf("주소록 방문에 실패하였습니다 > File Read Error!");
	}
	puts("");
}

void findToMsg(information lst[], char tmp[]) {
	int i = 0;
	while (i < 5) {
		if (strcmp(lst[i].name, tmp) == 0) {
			puts("");
			printf("[검색성공]\n");
			puts("==============");
			printf("이름: %s\n주소: %s\n나이: %d\n", lst[i].name, lst[i].address, lst[i].age);
			printf("검색 프로그램을 종료합니다.");
			exit(1);
		}
		i++;
	}
	msgFail(3);
}

int main(void) {
	FILE* fp;
	information d[5];
	char tmp[10];

	msgGetName();
	scanf("%s", tmp);

	fp = fopen("info.bin", "rb");
	if (fp == NULL) {
		msgFail(1);
		exit(1);
	}

	if (fread(&d, sizeof(information), 5, fp) != 5) {
		msgFail(2);
		exit(1);
	}

	findToMsg(d, tmp);
	fclose(fp);
	return 0;
}