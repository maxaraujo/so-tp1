#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

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

void imprimiOwner(char *str, char processo[]){
	struct stat sb;
    //char outstr[200];	
	
	strcpy(str, "/proc/");				
	strcat(str, processo);			
	strcat(str, "/stat");

	stat(str, &sb);
	struct passwd *pw = getpwuid(sb.st_uid);
	printf("|%s", pw->pw_name);
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

int func(char str[], int *numProc) 
{
	int a;
	FILE *fp;
	char str2[100], pchTemp[100], str3[100], word[100], str4[100], str5[100];	
	
    

	limpaString(str2);
	limpaString(pchTemp);
	fp = fopen (str,"r");	     
	
	//so vai imprimir o processo se ainda nao imprimiu 20 processos
	if (*numProc > 20)
		return 0;
	
	while (fscanf(fp,"%s", word) != EOF) {    
		//so vai imprimir o processo se ainda nao imprimiu 20 processos
		if(*numProc < 20){
			printf("|%s", word);
			*numProc = *numProc + 1;

		for (a = 0; a < 8 - (strlen(word)); a++)
			printf(" ");

		arquivoNomeProcesso(str3, word);
		arquivoNomeEstado(str4, word);				
			
		imprimiOwner(str5, word);	
			
		retornarNomeProcesso(str3,pchTemp);
		//retornarNomeProcesso(str4,pchTemp);
		arquivoFilhos(str2, word);
		//chamando o filho do processo atual
		func(str2, numProc);
	}else
			break;
	}
	fclose(fp);
	return 0;	
}

int main(){
	char str[100], str2[100], str3[100];
	int numProc = 0;
	printf("|PID     | User    | PROCNAME | Estado |\n");
	printf("-------------------------------\n");
	//printf("|1       ");
	//arquivoNomeProcesso(str,"1");
	//retornarNomeProcesso(str,str2);
	//imprimiOwner(str3,"1");
	func("/proc/1/task/1/children", &numProc);
    return 0;
}
