#include "criminal.h"
#ifndef DEBUG
#define DEBUG
#endif
// 애플리케이션용 함수 원형
void create_record();
void read_record();
void delete();
void read_file();
void file_r_Report();
void save_Wicked();

int main(){
	c_init();

	int menu;
	while(1){
		printf("\nMenu : 1.Create 2.Read 4.Delete 5.Read file 6.Read Report 7.Save_Wicked 0.Quit > ");
		scanf("%d", &menu);
		printf("\n");
		switch(menu){
			case 1:
				create_record();
				break;
			case 2:
				read_record();
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
			case 0:
			default:
				return 0;
		}
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

