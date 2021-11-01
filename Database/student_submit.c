//***************************************************************
//                   HEADER FILE USED IN PROJECT
//***************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

//typedef decltype(errno) errno_t;
//***************************************************************
//                   STURUCTURE USED IN PROJECT
//****************************************************************

struct student
{
	int rollno;
	char name[50];
	int p_marks, c_marks;
	double per;
	char grade;
	bool delete; //student의 삭제 여부를 표시하는 멤버변수
}st;

//***************************************************************
//        global declaration
//****************************************************************

FILE *fptr;

//***************************************************************
//        function to write in file
//****************************************************************

void create_student_struct() //write_student()에서 새로운 학생 정보를 삽입하는 역할
{
	printf("\nPlease Enter The New Details of student \n");
	printf("\nEnter The roll number of student : ");
	scanf("%d", &st.rollno); //scanf_s 함수를 mac os에 맞춰서 scanf()로 수정함.
	getchar(); //_getch 함수를 mac os에 맞춰서 getchar()로 수정함. //scanf로 값을 입력받은 후 버퍼에 남은 '\n'값을 비워주기 위해서 사용.
	printf("\n\nEnter The Name of student : ");
	gets(st.name); //gets_s 함수를 mac os에 맞춰서 gets()로 수정함.
	printf("\nEnter The marks in physics out of 100 : ");
	scanf("%d", &st.p_marks);
	printf("\nEnter The marks in chemistry out of 100 : ");
	scanf("%d", &st.c_marks);
	getchar();
	st.per = (st.p_marks + st.c_marks) / 2.0;
	if (st.per >= 60)
		st.grade = 'A';
	else if (st.per >= 50 && st.per<60)
		st.grade = 'B';
	else if (st.per >= 33 && st.per<50)
		st.grade = 'C';
	else
		st.grade = 'F';
	st.delete = false; //새로 생성하는 학생 정보마다 삭제여부를 표시하는 변수를 false로 초기화한다.
}

void write_student() //새로운 학생 정보를 중복 여부를 확인하고 삽입하는 함수
{
	struct student st_file;
	int	deleted_flag = 0;

	fptr = fopen("student.dat", "rb+"); //fopen_s 함수를 mac os에 맞게 fopen()으로 수정함. 
	//student.dat파일이 존재하는 경우 읽고 쓰기 옵션으로 파일을 연다.
	//append 옵션을 주지 않은 이유는 학생 정보를 delete하는 경우에, 맨 끝이 아닌 delete된 자리에 새로운 정보를 쓰기 위해서다.
	if (!fptr) //student.dat파일이 존재하지 않는 경우에는 위의 fopen에서 실패하고 if문을 실행한다.
	{
		fptr = fopen("student.dat", "ab+"); //파일에 끝에 쓰기 위해 append 옵션을 줘서 파일을 연다(작성한다).
		if (!fptr) //다시 fopen에서 실패한 경우
			return ;
		rewind(fptr); //쓰거나 읽을 위치를 처음으로 이동시킨다.
		create_student_struct(); //새로운 학생 정보 삽입하는 함수
		fwrite(&st, sizeof(st), 1, fptr);
		fclose(fptr);
		printf("\n\nStudent Record Has Been Created.  Press any key.... ");
		getchar();
		return ; //기존에 파일이 존재하지 않는 경우에 새로운 학생 정보를 삽입하고 종료한다.
	}
	create_student_struct(); //기존에 파일이 존재할때 새로운 학생 정보 삽입하는 경우
	while (fread(&st_file, sizeof(st_file), 1, fptr) > 0) //기존에 있는 파일의 학생 정보(st_file) 읽기
	{
		if ((st.rollno == st_file.rollno) && (st_file.delete == false)) 
		//새로운 학생 번호(st.rollno)와 기존 파일에 있는 학생 번호(st_file.rollno)가 같고
		//기존 파일에 있는 학생에 삭제 표시가 되어있지 않으면
		// = 새로 입력된 학생 번호가 중복의 경우
		{
			printf("\n\nStudent Record Already Exists.  Press any key.... ");
			fclose(fptr);
			getchar();
			return ;
		}
	} 
	//새로 입력된 학생 번호가 중복이 아닌 경우
	fclose(fptr);
	fptr = fopen("student.dat", "rb+"); //학생의 정보가 delete된 위치에 새로운 정보를 삽입하기 위해 r+b옵션으로 fopen한다.
	if (!fptr) //fopen 실패한 경우 종료
		return ;
	while (fread(&st_file, sizeof(st_file), 1, fptr) > 0) //기존에 있는 파일의 학생 정보(st_file) 읽기
	{
		if (st_file.delete == true) //delete 표시된 학생의 정보가 있으면
		{
			fseek(fptr, -sizeof(st_file), 1); //삭제된 데이터 뒤에 위치한 fptr를 현재 위치(SEEK_CUR, 1)에서 데이터의 크기만큼 앞으로 이동시킨다.
			fwrite(&st, sizeof(st), 1, fptr); //그리고 새로 입력한 학생 정보를 파일의 fptr위치에 쓴다.
			deleted_flag = 1; //새로운 학생 정보를 삭제된 학생 정보 자리에 덮어 썼다는 표시를 준다.
			break;
		}
	}
	if (deleted_flag == 0) //삭제된 학생 정보 자리에 덮어 쓰지 않은 경우
		fwrite(&st, sizeof(st), 1, fptr); //파일의 맨 뒤에 쓴다.
	fclose(fptr);
	printf("\n\nStudent Record Has Been Created.  Press any key.... ");
	getchar();
}


//***************************************************************
//        function to read all records from file
//****************************************************************


void display_all()
{
	int i;
	system("clear");
	printf("\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n");
	printf("====================================================\n");
	printf("R.No.  Name       P   C   Ave   Grade	\n");
	printf("====================================================\n");

	fptr = fopen("student.dat", "r+b");
	if (fptr == NULL)
		return;

	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0)
	{
		if (st.delete == 0)
		{
			printf("%-6d %-10s %-3d %-3d %-3.2f  %-1c\n", 
				st.rollno, st.name, st.p_marks, st.c_marks, st.per, st.grade);
		}
	}
	fclose(fptr);
	getchar();
}


//***************************************************************
//        function to read specific record from file
//****************************************************************


void display_sp(int n)
{
	int flag = 0;
	fptr = fopen("student.dat", "rb");
	if (fptr == NULL)
		return;
	while ((fread(&st, sizeof(st), 1, fptr)) > 0)
	{
		if (st.rollno == n && st.delete == false) //출력하고 싶은 학생의 정보가 delete표시가 없는 경우에만 출력
		{
			system("clear"); //cls 명령어를 mac os에 맞춰서 clear로 수정함.
			printf("\nRoll number of student : %d", st.rollno);
			printf("\nName of student : %s", st.name);
			printf("\nMarks in Physics : %d", st.p_marks);
			printf("\nMarks in Chemistry : %d", st.c_marks);
			printf("\nPercentage of student is  : %.2f", st.per);
			printf("\nGrade of student is : %c", st.grade);
			flag = 1;
		}
	}
	fclose(fptr);
	if (flag == 0)
		printf("\n\nrecord not exist");
	getchar();
}


//***************************************************************
//        function to modify record of file
//****************************************************************


void modify_student()
{
	int no, found = 0, i;

	system("clear");
	printf("\n\n\tTo Modify ");
	printf("\n\n\tPlease Enter The roll number of student : ");
	scanf("%d", &no);
	getchar();
	fptr = fopen("student.dat", "rb+");
	if (fptr == NULL)
		return;
	while ((i = fread(&st, sizeof(st), 1, fptr)) > 0 && found == 0)
	{
		if (st.rollno == no && st.delete == false) //수정하려는 학생의 정보가 delete표시가 없는 경우
		{
			printf("\nRoll number of student : %d", st.rollno);
			printf("\nName of student : %s", st.name);
			printf("\nMarks in Physics : %d", st.p_marks);
			printf("\nMarks in Chemistry : %d", st.c_marks);
			printf("\nPercentage of student is  : %.2f", st.per);
			printf("\nGrade of student is : %c", st.grade);
			printf("\nPlease Enter The New Details of student \n");
			printf("\nEnter The roll number of student ");
			scanf("%d", &st.rollno);
			getchar();
			printf("\n\nEnter The Name of student ");
			gets(st.name);
			printf("\nEnter The marks in physics out of 100 : ");
			scanf("%d", &st.p_marks);
			printf("\nEnter The marks in chemistry out of 100 : ");
			scanf("%d", &st.c_marks);

			st.per = (st.p_marks + st.c_marks) / 2.0;
			if (st.per >= 60)
				st.grade = 'A';
			else if (st.per >= 50 && st.per < 60)
				st.grade = 'B';
			else if (st.per >= 33 && st.per < 50)
				st.grade = 'C';
			else
				st.grade = 'F';
			st.delete = false; //modify하기 위해 생성하는 st구조체의 delete는 항상 false로 초기화해야 한다.
			//구조체가 전역변수로 선언되어, st.delete가 true로 변경되는 경우가 있을 수 있기 때문이다.

			fseek(fptr, -sizeof(st), 1);
			fwrite(&st, sizeof(st), 1, fptr);
			printf("\n\n\t Record Updated");
			found = 1;
			
			break;
		}
	}
	fclose(fptr);
	if (found == 0)
		printf("\n\n Record Not Found ");
	getchar();
}


//***************************************************************
//        function to delete record of file
//****************************************************************


void delete_student() //삭제할 학생 정보에 delete표시를 주는 함수
{
	int no;
	int	flag = 0;
	
	system("clear");
	printf("\n\n\n\tDelete Record");
	printf("\n\nPlease Enter The roll number of student You Want To Delete : ");
	scanf("%d", &no);
	getchar();
	fptr = fopen("student.dat", "rb+");
	if (fptr == NULL)
		return;
	rewind(fptr);

	while ((fread(&st, sizeof(st), 1, fptr))>0)
	{
		if (st.rollno == no) //기존 파일에 존재하는 학생의 번호와 삭제할 학생의 번호가 같은 경우
		{
			if (st.delete == true) //만약 delete표시가 있으면
				continue; //계속 진행한다.
			else //delete 표시가 없으면
			{
				st.delete = true; //delete표시를 한다.
				flag = 1; //delete표시를 했다는 flag
				break; //while문을 빠져나간다.
			}
		}
	}
	fseek(fptr, -sizeof(st), SEEK_CUR); //delete표시를 하기 위해 기존의 데이터 뒤에 위치한 fptr를 현재 위치(SEEK_CUR, 1)에서 데이터의 크기만큼 앞으로 이동시킨다.
	fwrite(&st, sizeof(st), 1, fptr); //그리고 delete표시를 한 학생 정보를 파일에 다시 쓴다.
	fclose(fptr);
	if (flag == 0) //delete표시를 했다는 flag가 0이면
		printf("No student whose rollno : %d, deletion failed.", no); //삭제에 실패했다고 출력
	else //delete표시를 했다는 flag가 1이면
		printf("\n\n\tRecord Deleted .."); //삭제했다고 출력
	getchar();
}



//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************
int main()
{
	char ch;
	int num;
	do
	{
		system("clear");

		printf("\n\n\t1.CREATE STUDENT RECORD");
		printf("\n\n\t2.DISPLAY ALL STUDENTS RECORDS");
		printf("\n\n\t3.SEARCH STUDENT RECORD ");
		printf("\n\n\t4.MODIFY STUDENT RECORD");
		printf("\n\n\t5.DELETE STUDENT RECORD");
		printf("\n\n\t6.EXIT");
		printf("\n\n\tPlease Enter Your Choice (1-6) ");
		ch = getchar();
		getchar();

		switch (ch)
		{
		case '1':	system("clear");
					write_student();
					break;
		case '2':	display_all();
					break;
		case '3':	system("clear");
					printf("\n\n\tPlease Enter The roll number : ");
					scanf("%d", &num);
					getchar();
					display_sp(num);
					break;
		case '4':	modify_student(); break;
		case '5':	delete_student(); break;
		case '6':	break;
		default:	printf("\a");
		}
	} while (ch != '6');
}
//***************************************************************
//                END OF PROJECT
//***************************************************************