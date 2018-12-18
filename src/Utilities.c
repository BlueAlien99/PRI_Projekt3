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
