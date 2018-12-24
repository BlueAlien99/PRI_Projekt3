#include "../include/Utilities.h"

_Bool clearBuffer(){
	_Bool clutter = 0;
	char c = getchar();
	while(c != ' ' && c != '\t' && c != '\n' && c != EOF){
		clutter = 1;
		c = getchar();
	}
	return clutter;
}

_Bool getString(char str[]){
	scanf(MLEN(MAX_STR), str);
	if(clearBuffer()){
		str = "";
		return 0;
	}
	return validateString(str);
}

_Bool getStringForm(char str[], char form[]){
	printf("%s: ", form);
	_Bool ret = getString(str);
	return ret;
}

_Bool validateString(char str[]){
	for(int i = 0; i < strlen(str); ++i){
		if(!(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= '0' && str[i] <= '9')){
			printf("> Invalid characters!\n");
			return 0;
		}
	}
	return 1;
}

_Bool verifyPesel(char p[], int sex){
	if(strlen(p) < PESEL_LEN){
		printf("\n> Too short!\n");
		return 0;
	}
	else if(strlen(p) > PESEL_LEN){
		printf("\n> Too long!\n");
		return 0;
	}
	if((p[9]-'0'+1)%2 != sex){
		printf("\n> Wrong sex!\n");
		return 0;
	}
	for(int i = 0; i < strlen(p); ++i){
		if(p[i] < '0' || p[i] > '9'){
			printf("\n> Invalid characters!\n");
			return 0;
		}
	}
	int ctrl = 0;
	int w[] = {9, 7, 3, 1, 9, 7, 3, 1, 9, 7};
	for(int i = 0; i < PESEL_LEN-1; ++i){
		ctrl += (p[i]-'0')*w[i];
	}
	if(ctrl%10 != (p[10]-'0')){
		printf("\n> Checksum error!\n");
		return 0;
	}
	printf("\n> OK!\n");
	return 1;
}

void upFirstLowRest(char str[]){
	if(strlen(str) > 0){
		str[0] = toupper(str[0]);
	}
	for(int i = 1; i < strlen(str); ++i){
		str[i] = tolower(str[i]);
	}
}

int getInt(){
	int x;
	if(scanf("%d", &x) != 1){
		clearBuffer();
		return -1;
	}
	else if(clearBuffer()){
		return -1;
	}
	return x;
}

int getIntForm(char form[]){
	printf("%s: ", form);
	return getInt();
}

char* strGen(int min, int max){
	int l = min + rand() % (max-min+1);
	char *str = malloc(l+1);
	if(str == NULL){
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < l; ++i){
		int c = 'a' + rand() % ('z'-'a'+1);
		str[i] = c;
	}
	str[0] = toupper(str[0]);
	str[l] = '\0';
	return str;
}

char* numGen(int l){
	char *str = malloc(l+1);
	if(str == NULL){
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < l; ++i){
		int c = '0' + rand() % ('9'-'0'+1);
		str[i] = c;
	}
	str[l] = '\0';
	return str;
}

int intGen(int min, int max){
	return min + rand() % (max-min+1);
}

int max(int a, int b){
	return a > b ? a : b;
}

int min(int a, int b){
	return a < b ? a : b;
}
