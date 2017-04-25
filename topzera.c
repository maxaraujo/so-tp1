#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void limpaString(char *str){
	strcpy(str,"");
}

void arquivoNomeProcesso(char *str, char processo[]){
		strcpy(str, "/proc/");				
		strcat(str, processo);		
		strcat(str, "/task/");			
		strcat(str, processo);		
		strcat(str, "/comm");
}

void arquivoNomeEstado(char *str, char processo[]){
		strcpy(str, "/proc/");				
		strcat(str, processo);			
		strcat(str, "/status");
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
			printf("|%s\n", str2);
			limpaString(str2);
		}		
	fclose(fp);
}

int func(char str[], int espaco) 
{
	int a;	
	FILE *fp;
	char str2[100], pchTemp[100], str3[100], word[100], str4[100];
	limpaString(str2);
	limpaString(pchTemp);
	fp = fopen (str,"r");	      

	while (fscanf(fp,"%s", word) != EOF) {    
		//for (a=0; a<espaco;a++)
				 	//strcat(pchTemp, "__");
		
		printf("|%s", word);

		for (a = 0; a < 8 - (strlen(word)); a++)
			printf(" ");
		
		arquivoNomeProcesso(str3, word);

		arquivoNomeEstado(str4, word);		

		retornarNomeProcesso(str3,pchTemp);

		//retornarNomeProcesso(str4,pchTemp);
		
		arquivoFilhos(str2, word);
		
		func(str2, espaco+1);
	}
	fclose(fp);
	return 0;	
}

int main(){
	char str[100], str2[100];
	printf("|PID     | User    | PROCNAME | Estado |\n");
	printf("-------------------------------\n");
	printf("|1       ");
	arquivoNomeProcesso(str,"1");
	retornarNomeProcesso(str,str2);
	func("/proc/1/task/1/children", 1);
    return 0;
}
