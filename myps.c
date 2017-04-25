                        
[00:28, 25/4/2017] Cesar Augusto: #include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void arquivoNomeProcesso(char *str, char processo[]){
		strcpy(str, "/proc/");				
		strcat(str, processo);		
		strcat(str, "/task/");			
		strcat(str, processo);		
		strcat(str, "/comm");
}

void arquivoFilhos(char *str, char processo[]){
		strcpy(str, "/proc/");				
		strcat(str, processo);		
		strcat(str, "/task/");			
		strcat(str, processo);		
		strcat(str, "/children");
}

void retornarNomeProcesso(char str[], char *str2){
	FILE *fp;
	char word[100];
	
	fp = fopen (str,"r");	
		
		while (fscanf(fp,"%s", word) != EOF) { 
			strcat(str2, word);
			printf("%s \n", str2);
			strcpy(str2,"");
		}	
	
	fclose(fp);
}

int func(char str[], int espaco) 
{
	int a;	
	FILE *fp;
	char *pch, line[1000], str2[100], pchTemp[100], str3[100], word[100],word2[100];
	strcpy(str2,"");
	strcpy(pchTemp,"");
	fp = fopen (str,"r");	      

	while (fscanf(fp,"%s", word) != EOF) {    
		for (a=0; a<espaco;a++)
				 	strcat(pchTemp, "__");
		
		arquivoNomeProcesso(str3, word);	
		retornarNomeProcesso(str3,pchTemp);
		
		strcpy(str2, "");		
		arquivoFilhos(str2, word);
		
		func(str2, espaco+1);
	}
	fclose(fp);
	return 0;	
}

main(){
	char str[100], str2[100];
	
	arquivoNomeProcesso(str,"1");
	retornarNomeProcesso(str,str2);
	func("/proc/1/task/1/children", 1);

}                        
[00:30, 25/4/2017] Cesar Augusto: #include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void arquivoNomeProcesso(char *str, char processo[]){
		strcpy(str, "/proc/");				
		strcat(str, processo);		
		strcat(str, "/task/");			
		strcat(str, processo);		
		strcat(str, "/comm");
}

void arquivoFilhos(char *str, char processo[]){
		strcpy(str, "/proc/");				
		strcat(str, processo);		
		strcat(str, "/task/");			
		strcat(str, processo);		
		strcat(str, "/children");
}

void retornarNomeProcesso(char str[], char *str2){
	FILE *fp;
	char word[100];
	
	fp = fopen (str,"r");	
		
		while (fscanf(fp,"%s", word) != EOF) { 
			strcat(str2, word);
			printf("%s \n", str2);
			strcpy(str2,"");
		}	
	
	fclose(fp);
}

int func(char str[], int espaco) 
{
	int a;	
	FILE *fp;
	char str2[100], pchTemp[100], str3[100], word[100];
	strcpy(str2,"");
	strcpy(pchTemp,"");
	fp = fopen (str,"r");	      

	while (fscanf(fp,"%s", word) != EOF) {    
		for (a=0; a<espaco;a++)
				 	strcat(pchTemp, "__");
		
		arquivoNomeProcesso(str3, word);	
		retornarNomeProcesso(str3,pchTemp);
		
		strcpy(str2, "");		
		arquivoFilhos(str2, word);
		
		func(str2, espaco+1);
	}
	fclose(fp);
	return 0;	
}

int main(){
	char str[100], str2[100];
	
	arquivoNomeProcesso(str,"1");
	retornarNomeProcesso(str,str2);
	func("/proc/1/task/1/children", 1);
    return 0;
}
