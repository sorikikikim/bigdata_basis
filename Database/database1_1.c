#include <stdio.h>
#include <stdlib.h>

typedef struct s_student
{
	char	name[50];
	char	address[50];
	int		age;
}	t_student;

int main(void)
{
	FILE	*fp;
	int		i;
	t_student 	st[5];

	for (int i = 0; i < 5; i++){
		printf("%d번째 입력입니다\n", i + 1);
		printf("이름 : ");
		scanf("%s", st[i].name);
		printf("주소 : ");
		scanf("%s", st[i].address);
		printf("나이 : ");
		scanf("%d", &st[i].age);
		printf("\n");
	}
	fp = fopen("student.bin", "wb");
	if (fp == NULL)
	{
		printf("File open error!\n");
		exit(1);
	}
	if (fwrite(&st, sizeof(t_student), 5, fp) != 5)
	{
		printf("File write error!\n");
		exit(1);
	}
	printf(" 학생이름 |   주소  |  나이\n");
	printf("-----------------------------\n");
	for (i = 0; i < 5; i++)
		printf("%12s | %10s | %4d\n", st[i].name, st[i].address, st[i].age);
	fclose(fp);
	return 0;
}