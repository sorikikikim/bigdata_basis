#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	char name[10];
	char address[100];
	int age;
}information;

int main(void) {
	FILE* fp;
	information d[5];

	for (int i = 0; i < 5; i++) {
		printf("%d번째 입력입니다\n", i+1);
		printf("이름: ");
		scanf("%s", d[i].name);
		printf("주소: ");
		scanf("%s", d[i].address);
		printf("나이: ");
		scanf("%d", &d[i].age);
		printf("\n");
	}

	fp = fopen("info.bin", "wb");
	if (fp == NULL) {
		printf("File Open Error!\n");
		exit(1);
	}

	if (fwrite(&d, sizeof(information), 5, fp) != 5) {
		printf("File Write Error!");
		exit(1);
	}

	for (int i = 0; i < 5; i++) {
		printf("%d: %s / %s / %d\n", i, d[i].name, d[i].address, d[i].age);
	}
	return 0;
}