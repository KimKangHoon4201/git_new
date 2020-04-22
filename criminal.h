#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CRIMINALS 90
#define MAX_USER 5

// 범죄자 레코드의 데이터 타입 정의
typedef struct login{
	char id[20];
	char password[20];
}Login;

typedef struct category{ // 범죄항목
	char crim1[20];
	char crim2[20];
	char crim3[20];
	char crim4[20];
	char crim5[20];
}Crim;

typedef struct criminal{
	char name[20]; //범죄자 이름
	int age;
	char sex[20];
	char city[20];
	Crim crim;
	int  record;
}Criminal_Info;

// 라이브러리 함수 원형을 선언
int c_count();
int c_is_available();
int c_first_available();
Criminal_Info* c_search_by_name(char* n);
void c_create(char* n, int a, char* s, char* c, char* c1, char* c2, char* c3, char* c4, char* c5, int r);
void c_file_r();
int c_search_by_sex(Criminal_Info* a[], char* n);
void search_sex(char* n);
int c_search_by_city(Criminal_Info* a[], char* n);
void search_city(char* n);
int c_search_by_category(Criminal_Info* a[], char* n);
void search_category(char* n);
	int c_search_by_age(Criminal_Info* a[], int n);
void search_age(int n);
	char* c_to_string(Criminal_Info* p);
	void c_get_all(Criminal_Info* a[]);
	char* c_getname(Criminal_Info* p);
	int c_getage(Criminal_Info* p);
	char* c_getsex(Criminal_Info* p);
	char* c_getcity(Criminal_Info* p);
	char* c_getcategory1(Criminal_Info* p);
	char* c_getcategory2(Criminal_Info* p);
	char* c_getcategory3(Criminal_Info* p);
	char* c_getcategory4(Criminal_Info* p);
	char* c_getcategory5(Criminal_Info* p);
	int c_getrecord(Criminal_Info* p);
	char* c_file_s(Criminal_Info* p);
	char* c_stat_s();
	void file_s();
	void c_init();
	void c_delete(Criminal_Info* p);
	void file_r_List();//파일 새로 읽어서 출력
	void file_r_Wicked();
	int search_wicked(Criminal_Info* a[]);
	void c_update(Criminal_Info* p, char* city);
	void c_update_category(Criminal_Info* p);
	Login* c_search_by_id(char* n);
	int	c_id_available();
	void c_create_user(char* id, char* pw);
	int c_first_id_available();
	int c_count();
	void c_get_user_all(Login* a[]);
	void c_save_user();
	char* c_file_user_s(Login* p);
	void c_user_file_r();
	void c_init_id();
	void c_optimize_record();
	int get_last();
	void c_free_record(int index);
	void c_sort_record();
