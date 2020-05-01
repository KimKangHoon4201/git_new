#include "criminal.h"

Criminal_Info* criminals [MAX_CRIMINALS];
Login* user[MAX_USER];
int _count = 0;
int _user =0;



int c_count(){
	return _count;
}

int c_user_count(){
	return _user;
}

int c_is_available(){
	for(int i=0; i<MAX_CRIMINALS; i++){
		if(criminals[i]==NULL) return 1;
	}
	return 0;
}

int c_first_available(){
	for(int i=0; i<MAX_CRIMINALS; i++){
		if(criminals[i]==NULL) return i;
	}
	return -1;
}

Criminal_Info* c_search_by_name(char* n){
	for(int i=0; i<_count; i++){
		if(criminals[i]!=NULL && strcmp(criminals[i]->name, n)==0) return criminals[i];
	}
	return NULL;
}

void c_create(char* n, int a, char* s, char* c, char* c1, char* c2, char* c3, char* c4, char* c5, int r){
	int index = c_first_available();
	criminals [index] = (Criminal_Info*)malloc(sizeof(Criminal_Info));
	Criminal_Info* p = criminals[index];
	strcpy(p->name, n);
	p->age = a;
	strcpy(p->sex, s);
	strcpy(p->city, c);
	strcpy(p->crim.crim1, c1);
	strcpy(p->crim.crim2, c2);
	strcpy(p->crim.crim3, c3);
	strcpy(p->crim.crim4, c4);
	strcpy(p->crim.crim5, c5);
	p->record = r;
	_count++;
}
 // 범죄자 정보로 신규 레코드 추가

void c_file_r(){
	FILE *fp = fopen("Criminal_List.txt", "r");
	char name[20], sex[20], city[20], category1[20], category2[20], category3[20]
	, category4[20], category5[20];
	int age, record;
	while(!feof(fp)){
		if(!c_is_available()){
		printf("[Load] There is no space!\n");
		break;
	}
	int n= fscanf(fp, "%s %d %s %s %s %s %s %s %s %d", name, &age, sex, city, category1,
category2, category3, category4, category5, &record);
	if(n<10) break;

	if(c_search_by_name(name)) {
		printf("[Load] Duplicated name(%s)! loding.\n", name);
		continue;
	}
	c_create(name, age, sex, city, category1, category2, category3, category4, category5, record);
	#ifdef DEBUG
	printf("[DEBUG] read a record from file -%s\n", name);
	#endif
}
#ifdef DEBUG
printf("[DEBUG]%d records are read from file!\n", c_count());
#endif
fclose(fp);
}




int c_search_by_sex(Criminal_Info* a[], char* n){
	int i, c=0;
	for(i=0; i<MAX_CRIMINALS; i++){
			if(criminals[i]!=NULL && (strcmp(criminals[i]->sex, n)==0)){
					a[c]=criminals[i];
					c++;
			}
	}
	return c;
}

void search_sex(char* n){
	Criminal_Info* records[MAX_CRIMINALS];
	int size = c_search_by_sex(records, n);
	printf("%d records found.\n", size);
	for(int i=0; i<size; i++){
		Criminal_Info* p = records[i];
		printf("%d. %s\n", i+1, c_to_string(p));
	}
}


int c_search_by_city(Criminal_Info* a[], char* n){
	int i, c=0;
	for(i=0; i<MAX_CRIMINALS; i++){
			if(criminals[i]!=NULL && (strcmp(criminals[i]->city, n)==0)){
					a[c]=criminals[i];
					c++;
			}
	}
	return c;
}

void search_city(char* n){
	Criminal_Info* records[MAX_CRIMINALS];
	int size = c_search_by_city(records, n);
	printf("%d records found.\n", size);
	for(int i=0; i<size; i++){
		Criminal_Info* p = records[i];
		printf("%d. %s\n", i+1, c_to_string(p));
	}
}


int c_search_by_category(Criminal_Info* a[], char* n){
	int i, c=0;
	for(int i=0; i<MAX_CRIMINALS; i++){
		if(criminals[i]!=NULL && (strcmp(criminals[i]->crim.crim1, n)==0||strcmp(criminals[i]->crim.crim2, n)==0
		||strcmp(criminals[i]->crim.crim3, n)==0||strcmp(criminals[i]->crim.crim4, n)==0||strcmp(criminals[i]->crim.crim5 , n)==0)){
			a[c]=criminals[i];
			c++;
		}
	}
	return c;
}
void search_category(char* n){
	Criminal_Info* records[MAX_CRIMINALS];
	int size = c_search_by_category(records, n);
	printf("%d records found.\n", size);
	for(int i=0; i<size; i++){
		Criminal_Info* p = records[i];
		printf("%d. %s\n", i+1, c_to_string(p));
	}
}


// Menu : 1. 20s & 30s 2. 40s & 50s 3. Older
	int c_search_by_age(Criminal_Info* a[], int n){
		int i, j, c=0;
		if(n==1){
		for(i=0; i<MAX_CRIMINALS; i++){
			for(j=20; j<40; j++){
				if(criminals[i]!=NULL && criminals[i]->age==j){
					a[c]=criminals[i];
					c++;
				}
			}
		}
	}//20대, 30대 찾기
	else if(n==2){
		for(i=0; i<MAX_CRIMINALS; i++){
			for(j=40; j<60; j++){
				if(criminals[i]!=NULL && criminals[i]->age==j){
					a[c]=criminals[i];
					c++;
				}
			}
		}
	}//40대, 50대 찾기
	else if(n==3){
		for(i=0; i<MAX_CRIMINALS; i++){
			for(j=60; j<=100; j++){
				if(criminals[i]!=NULL && criminals[i]->age==j){
					a[c]=criminals[i];
					c++;
				}
			}
		}
	}
	#ifdef DEBUG
	printf("[DEBUG]search until %d",j);
	#endif
	return c;
}

void search_age(int n){
	Criminal_Info* records[MAX_CRIMINALS];
	int size = c_search_by_age(records, n);
	printf("%d records found.\n", size);
	for(int i=0; i<size; i++){
		Criminal_Info* p = records[i];
		printf("%d. %s\n", i+1, c_to_string(p));
	}
}


	char* c_to_string(Criminal_Info* p){
		static char str[120];
		sprintf(str, "[%d] %s / %s / %s / %s  %s %s %s %s/ %d", p->age, p->name, p->sex
		, p->city, p->crim.crim1, p->crim.crim2, p->crim.crim3, p->crim.crim4
		, p->crim.crim5, p->record);
		return str;
	}

	void c_get_all(Criminal_Info* a[]){
		int c=0;
		for(int i=0; i<MAX_CRIMINALS; i++){
			if(criminals[i]!=NULL){
				a[c]=criminals[i];
				c++;
			}
		}
	}

	void c_get_user_all(Login* a[]){
		int c=0;
		for(int i=0; i<MAX_USER; i++){
			if(user[i]!=NULL){
				a[c]=user[i];
				c++;
			}
		}
	}
	char* c_getname(Criminal_Info* p){
		return p->name;
	}
	int c_getage(Criminal_Info* p){
		return p->age;
	}
	char* c_getsex(Criminal_Info* p){
		return p->sex;
	}
	char* c_getcity(Criminal_Info* p){
		return p->city;
	}
	char* c_getcategory1(Criminal_Info* p){
		return p->crim.crim1;
	}
	char* c_getcategory2(Criminal_Info* p){
		return p->crim.crim2;
	}
	char* c_getcategory3(Criminal_Info* p){
		return p->crim.crim3;
	}
	char* c_getcategory4(Criminal_Info* p){
		return p->crim.crim4;
	}
	char* c_getcategory5(Criminal_Info* p){
		return p->crim.crim5;
	}

	int c_getrecord(Criminal_Info* p){
		return p->record;
	}
	char* c_file_s(Criminal_Info* p){
		static char str[80];
		sprintf(str, "%s %d %s %s %s %s %s %s %s %d", p->name, p->age, p->sex
		, p->city, p->crim.crim1, p->crim.crim2, p->crim.crim3, p->crim.crim4,
		p->crim.crim5, p->record);
		return str;
	}
	char* c_stat_s(){
		Criminal_Info* C_age1[MAX_CRIMINALS];
		Criminal_Info* C_age2[MAX_CRIMINALS];
		Criminal_Info* C_age3[MAX_CRIMINALS];
		Criminal_Info* C_m[MAX_CRIMINALS];
		Criminal_Info* C_w[MAX_CRIMINALS];

		static char str[80];
		int age1 = c_search_by_age(C_age1, 1);
		int age2 = c_search_by_age(C_age2, 2);
		int age3 = c_search_by_age(C_age3, 3);
	  int m = c_search_by_sex(C_m, "men");
		int w = c_search_by_sex(C_w, "women");
		sprintf(str, "20,30's: %d 30,40's: %d older: %d men: %d women: %d", age1, age2, age3
		, m, w);
		return str;
	}

	void file_s(){
		FILE* f1 = fopen("Criminal_List.txt", "w");
		int size = c_count();
		Criminal_Info* records[size];
		c_get_all(records);
		for(int i=0; i<size; i++){
			Criminal_Info* p = records[i];
			fprintf(f1, "%s\n", c_file_s(p));
		}
		#ifdef	DEBUG
		printf("[DEBUG]ALL records are saved\n");
		#endif
		fclose(f1);
		FILE* f2 = fopen("Criminal_Report.txt", "w");
		fprintf(f2, "%s\n", c_stat_s());
		#ifdef DEBUG
		printf("[DEBUG]stats are saved\n");
		#endif
		fclose(f2);
	}

	void c_init(){
		for(int i=0; i<MAX_CRIMINALS; i++){
			if(criminals[i]!=NULL){
				free(criminals[i]);
			}
			criminals[i] = NULL;
			#ifdef DEBUG
			printf("[DEBUG]record %d is free\n", i);
			#endif
		}_count =0;
	} //모든 레코드 제거

	void c_init_id(){

			for(int i=0; i<MAX_USER; i++){
				if(user[i]!=NULL){
					free(user[i]);
				}
				user[i] = NULL;
			}_user =0;
	}
	void c_delete(Criminal_Info* p){
		int i, index;
		for(i=0; i<MAX_CRIMINALS; i++)
			if(criminals[i]==p){
				index=i;
				break;
				#ifdef DEBUG
				printf("[DEBUG]%s is 8", criminals[i]->name);
				#endif
			}
		free(p);
		criminals[index] = NULL;
		_count--;
	}

 void file_r_List(){
	FILE *fp = NULL;
	fp=fopen("Criminal_List.txt", "r");
	if( fp != NULL )
	{
		#ifdef DEBUG
		printf("[DEBUG]The List file is not empty");
		#endif
		char strTemp[255];
		char *pStr;

		while( !feof( fp ) )
		{
			pStr = fgets( strTemp, sizeof(strTemp), fp );
			printf( "%s", pStr );
		}
		fclose( fp );
	}
	else
	{
		#ifdef DEBUG
		printf("[DEBUG]The List file is empty");
		#endif
	}
		}

	void file_r_Wicked(){
		FILE *fp =  NULL;
		fp=fopen("Criminal_Wicked.txt", "r");
	if( fp != NULL )
	{
		#ifdef DEBUG
		printf("[DEBUG]The List file is not empty");
		#endif
		char strTemp[255];
		char *pStr;

		while( !feof( fp ) )
		{
			pStr = fgets( strTemp, sizeof(strTemp), fp );
			printf( "%s", pStr );
		}
		fclose( fp );
	}
	else
	{
		#ifdef DEBUG
		printf("[DEBUG]The Wicked file is empty");
		#endif
	}
}

	int search_wicked(Criminal_Info* a[]){
		int c=0;
		for(int i=0; i<MAX_CRIMINALS; i++){
			#ifdef DEBUG
			printf("[DEBUG]Searching wicked %d\n", i);
			#endif
			for(int j=3; j<=5; j++){
				if(criminals[i]!=NULL && criminals[i]->record==j){
					a[c]=criminals[i];
					c++;
				}
			}
		}

		return c;
	}

	void c_update(Criminal_Info* p, char* city){
		strcpy(p->city, city);
	}
	void c_update_category(Criminal_Info* p){
		char c1[20], c2[20], c3[20], c4[20], c5[20];
		printf("Update category!!!\n");
		printf("If you want to stop \"x+[Enter]\"\n");
		printf("category1: ");
		scanf("%s", c1);
		if(strcmp(c1,"x")==0){
			p->record=0;
			return;
		}else{
			strcpy(p->crim.crim1,c1);
			p->record=1;
		}
		printf("category2: ");
		scanf("%s", c2);
		if(strcmp(c2,"x")==0)	return;
		else{
			strcpy(p->crim.crim2,c2);
			p->record++;
		}
		printf("category3: ");
		scanf("%s", c3);
		if(strcmp(c3,"x")==0)	return;
		else{
			strcpy(p->crim.crim3,c3);
			p->record++;
		}
		printf("category4: ");
		scanf("%s", c4);
		if(strcmp(c4,"x")==0)	return;
		else{
			strcpy(p->crim.crim4,c4);
			p->record++;
		}
		printf("category5: ");
		scanf("%s", c5);
		if(strcmp(c5,"x")==0)	return;
		else{
			strcpy(p->crim.crim5,c5);
			p->record++;
		}
	}

	Login* c_search_by_id(char* n){
		for(int i=0; i<_user; i++){
			if(user[i]!=NULL && strcmp(user[i]->id, n)==0) return user[i];
		}
		return NULL;
	}

 	int	c_id_available(){
		for(int i=0; i<MAX_USER; i++){
			if(user[i]==NULL) return 1;
		}
		return 0;
	}

	void c_create_user(char* id, char* pw){
		int index = c_first_id_available();
		user [index] = (Login*)malloc(sizeof(Login));
		Login* p = user[index];
		strcpy(p->id, id);
		strcpy(p->password, pw);
		_user++;
		c_save_user(id, pw);
	}

	int c_first_id_available(){
		for(int i=0; i<MAX_USER; i++){
			if(user[i]==NULL) return i;
		}
		return -1;
	}

	void c_save_user(){
		FILE* f = fopen("User_List.txt", "w");
		int size = c_user_count();
		Login* records[size];
		c_get_user_all(records);
		for(int i=0; i<size; i++){
			Login* p = records[i];
			fprintf(f, "%s\n", c_file_user_s(p));
		}
		fclose(f);
	}
	char* c_file_user_s(Login* p){
		static char str[80];
		sprintf(str, "%s %s ", p->id, p->password);
		return str;
	}

	void c_user_file_r(){
		FILE *fp = fopen("User_List.txt", "r");
		char ID[20], PW[20];
		while(!feof(fp)){
			if(!c_id_available()){
			printf("[Load] There is no space!\n");
			break;
			}
		int n= fscanf(fp, "%s %s", ID, PW);
		if(n<2) break;

		if(c_search_by_name(ID)) {
			printf("[Load] Duplicated ID(%s)! loding.\n", ID);
			continue;
		}
		c_create_user(ID, PW);
	}
	#ifdef DEBUG
	int i=0;
	for(;;){
	if(user[i]==NULL) break;
	printf("%s", user[i]->id);
	}
	#endif
	fclose(fp);
	}

	int get_last(){
		int last=MAX_CRIMINALS-1;//마지막 레코드 인덱스
		while(criminals[last]==NULL){
			last--;
		}
		return last;
	}

	void c_optimize_record(int last){
		int index = c_first_available();

		for(int i= index; i<last; i++){
			criminals[i]=criminals[i+1];
		}
	}

	void c_free_record(int index){
		free(criminals[index]);
		criminals[index]=NULL;
	}

	void c_sort_record(){
		int n = c_count();
			for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < n - i - 1; j++){ // last i elements are already in place
# ifdef DEBUG
printf("sorting\n");
# endif
		if (strcmp(criminals[j]->name, criminals[j+1]->name)>0){
						#ifdef DEBUG
						printf("swap\n");
						#endif
						Criminal_Info* tmp;
						tmp = criminals[j+1];
						criminals[j+1]=criminals[j];
						criminals[j]=tmp;
					}
				}

			}

	}

