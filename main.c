#include "criminal.h"
#ifndef DEBUG
#define DEBUG
#endif
// 애플리케이션용 함수 원형
void create_record();
void read_record();
void update_record();
void delete();
void read_file();
void file_r_Report();
void save_Wicked();
int login();
void create_user();
void Optimize_record();
void Sort_Record();

int main(){
	c_init_id();
	c_user_file_r();
	int i;
	if(c_first_id_available()>0){
		i=login();
			if(i==0) return 0;
	}
	c_init();
	int menu;
	while(1){
		printf("\nMenu : 1.Create 2.Read 3.Update 4.Delete 5.Read_file 6.Read_Report 7.Save_Wicked 8.Optimize_record 9.Sort_Record 10.Create_user 0.Quit > ");
		scanf("%d", &menu);
		printf("\n");
		switch(menu){
			case 1:
				create_record();
				break;
			case 2:
				read_record();
				break;
			case 3:
				update_record();
				break;
			case 4:
				delete();
				break;
			case 5:
				read_file();
				break;
			case 6:
				file_r_Report();
				break;
			case 7:
				save_Wicked();
				break;
			case 8:
				Optimize_record();
				break;
			case 9:
				Sort_Record();
				break;
			case 10:
				create_user();
				break;
			case 0:
			default:
				return 0;
		}
	}
}

int login(){
	char id[20], pw[20];
	printf("Enter ID: ");
	scanf("%s", id);
	Login* p = c_search_by_id(id);
	if(p){
		printf("Enter Password: ");
		scanf("%s", pw);
		if(strcmp(p->password,pw)==0)
			return 1;
		else{
			printf("incorrection of password\n");
			return 0;
		}
	}else{
	 printf("No such ID\n");
	 return 0;
	}
}

void create_record(){
	char name[20], sex[20], city[20], category[20];
	int age, record;
	char* c2="x";
	char* c3="x";
	char* c4="x";
	char* c5="x";
	c_file_r();
	if(c_is_available()){
	printf("Enter a new criminal's info.\n");
	printf("Name > ");
	scanf("%s", name);
	if(c_search_by_name(name)) {
		printf("Duplicated name!\n");
		return;
	}
	printf("age(20~100) > ");
	scanf("%d", &age);
	if(age<20 || age>100){
		printf("This is not reasonable age");
		return;
	}
	printf("sex(men, women) > ");
	scanf("%s", sex);
	if(strcmp(sex,"men")==0 || strcmp(sex,"women")==0){
	}else{
		printf("This is not reasonable sex");
		return;
	 }
	printf("city > ");
	scanf("%s", city);
	printf("category > ");
	scanf("%s", category);
	record = 1;
	c_create(name, age, sex, city, category, c2, c3, c4, c5, record);
	}else{
	printf("There is no space!\n");
	return;
	}
}

void read_record(){
	int read_menu;
	char name[20];
	int age_menu;
	char sex[20];
	char city[20];
	char category[20];
	printf("\nMenu : 1.all 2.name 3.age 4.sex 5.city 6.category 7.save file 0.Quit > ");
	scanf("%d", &read_menu);
	printf("\n");
	switch(read_menu){
		case 1:
	  printf("All records\n");
		int size = c_count();
		Criminal_Info* records[MAX_CRIMINALS];
		c_get_all(records);
		for(int i=0; i<size; i++){
			Criminal_Info* p = records[i];
			printf("%d. %s\n", i+1, c_to_string(p));
		}
		break;
		case 2:
		printf("Enter a name > ");
		scanf("%s", name);
		Criminal_Info* p = c_search_by_name(name);
		if(p) {
			printf("Criminal info.\n");
			printf("Name : %s\n", c_getname(p));
			printf("Age : %d\n", c_getage(p));
			printf("Sex : %s\n", c_getsex(p));
			printf("City : %s\n", c_getcity(p));
			printf("Category : %s %s %s %s %s\n", c_getcategory1(p), c_getcategory2(p)
		, c_getcategory3(p), c_getcategory4(p), c_getcategory5(p));
			//printf("Record : %d\n", c_getrecord(p));
		}else{
			printf("No such criminal");
			return;
		}
		break;
		case 3:
			printf("Menu : 1. 20s & 30s 2. 40s & 50s 3. Older ~ 100 > ");
			scanf("%d", &age_menu);
		  search_age(age_menu);
			break;
		case 4:
			printf("Enter a sex > ");
			scanf("%s", sex);
	  	search_sex(sex);
			break;
		case 5:
			printf("Enter a city > ");
			scanf("%s", city);
			search_city(city);
			break;
		case 6:
			printf("Enter a category > ");
			scanf("%s", category);
			search_category(category);
			break;
		case 7:
			file_s();
			break;
		case 0:
		default:
			return;
		}
	}

void update_record(){
	char name[20], city[20], c1[20], c2[20], c3[20], c4[20], c5[20];
	printf("Enter a name > ");
	scanf("%s", name);
	int yesno;

	Criminal_Info* p = c_search_by_name(name);
	if(p) {
		printf("Enter a update info.\n");
		printf("city > ");
		scanf("%s", city);
		c_update(p, city);
		printf("Are you going to update the crime classification?\n");
		printf("yes:1 no:2 > ");
		scanf("%d", &yesno);
		if(yesno==1){
			if(p->record>=5)
				printf("There is no space");
			else
				c_update_category(p);
		}else return;
	}else{
		printf("No such criminal!\n");
	}
}

void delete(){
	char  name[20];
	printf("Enter a name: ");
	scanf("%s", name);

	Criminal_Info* p = c_search_by_name(name);
	if(p) {
		c_delete(p);
		printf("The record is delete!\n");
	}else {
		printf("No such member!\n");
	}
	file_s();
}

	void read_file(){
		printf("<List file>\n");
		file_r_List();
		printf("<Wicked file>\n");
		file_r_Wicked();
	}

	void file_r_Report(){
		FILE *fp = fopen("Criminal_Report.txt", "r");
		char stat_arr_age1[10];
		char stat_arr_age2[10];
		char stat_arr_age3[10];
		char stat_arr_sex1[10];
		char stat_arr_sex2[10];
		int	age1;
		int age2;
		int age3;
		int sex1;
		int sex2;

		int n= fscanf(fp, "%s %d %s %d %s %d %s %d %s %d", stat_arr_age1, &age1, stat_arr_age2, &age2, stat_arr_age3, &age3, stat_arr_sex1, &sex1, stat_arr_sex2, &sex2);
		printf("%s %d %s %d %s %d %s %d %s %d\n", stat_arr_age1, age1, stat_arr_age2, age2, stat_arr_age3, age3, stat_arr_sex1, sex1, stat_arr_sex2, sex2);
		fclose(fp);
	}

	void save_Wicked(){
		FILE *fp = fopen("Criminal_Wicked.txt", "w");
		Criminal_Info* records[MAX_CRIMINALS];
		int size=search_wicked(records);
		for(int i=0; i<size; i++){
			fprintf(fp, "%s\n", c_file_s(records[i]));
		}
		fclose(fp);
	}

	void create_user(){
		char id[20], pw[20];
		if(c_id_available()){
		printf("Enter a new user's info.\n");
		printf("ID > ");
		scanf("%s", id);
		if(c_search_by_name(id)) {
			printf("Duplicated ID!\n");
			return;
		}
		printf("Password > ");
		scanf("%s", pw);
		c_create_user(id, pw);
  	c_save_user(id, pw);
		}else{
		printf("There is no space!\n");
		return;
		}
	}

	void Optimize_record(){
		int last =get_last();
		printf("[Before]first_available:%d, count:%d\n", c_first_available(), c_count());
		if(last>c_first_available()){
		c_optimize_record(last);
		c_free_record(last);
		}
		printf("[After]first_available:%d, count:%d\n", c_first_available(), c_count());
	}

	void Sort_Record(){
		printf("Records were sorted\n");
		Criminal_Info* records[MAX_CRIMINALS];
		int size = c_count();
		c_sort_record();
		c_get_all(records);
		for(int i=0; i<size; i++){
			Criminal_Info* p = records[i];
			printf("%d. %s\n", i+1, c_to_string(p));
		}
	}

