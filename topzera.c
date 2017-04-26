#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <signal.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


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
        int i;
		strcpy(str, "/proc/");				
		strcat(str, processo);			
		strcat(str, "/status");
		
		FILE *fp;
	    char word[100];
	
	    fp = fopen (str,"r");
	    for(i = 0; i < 6; i++){
	        fscanf(fp,"%s", word);
	    }
		
		printf("|%s",word);
		
		for (i = 0; i < 8 - (strlen(word)); i++)
			printf(" ");
			
		printf("|\n");
		
		fclose(fp);
		
}

void imprimiOwner(char *str, char processo[], char *owner){
	struct stat sb;
    limpaString(owner);
	
	strcpy(str, "/proc/");				
	strcat(str, processo);			
	strcat(str, "/stat");

	stat(str, &sb);
	struct passwd *pw = getpwuid(sb.st_uid);
	printf("|%s", pw->pw_name);
	strcpy(owner, pw->pw_name);
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
	int a;
	char word[100];
	
	fp = fopen (str,"r");	
		
		while (fscanf(fp,"%s", word) != EOF) { 
			strcat(str2, word);
			printf("|%s", str2);
			limpaString(str2);
		}
		for (a = 0; a < 20 - (strlen(word)); a++)
			printf(" ");		
	fclose(fp);
}

int func(char str[], int *numProc) 
{
	int a;
	FILE *fp;
	char str2[100], pchTemp[100], str3[100], word[100], str4[100], str5[100], owner[100];	    

	limpaString(str2);
	limpaString(pchTemp);
	fp = fopen (str,"r");	     
	
	//so vai imprimir o processo se ainda nao imprimiu 20 processos
	//if (*numProc > 80)
	//	return 0;
	
	while (fscanf(fp,"%s", word) != EOF) {    
		//so vai imprimir o processo se ainda nao imprimiu 20 processos
		//if(*numProc < 80){
			printf("|%s", word);
			//*numProc = *numProc + 1;
		//acertando o layout	
		for (a = 0; a < 8 - (strlen(word)); a++)
			printf(" ");

		arquivoNomeProcesso(str3, word);
						
			
		imprimiOwner(str5, word, owner);	
		//acertando o layout	
		for (a = 0; a < 15 - (strlen(owner)); a++)
			printf(" ");
			
		retornarNomeProcesso(str3,pchTemp);
		
		arquivoNomeEstado(str4, word);
		
		//retornarNomeProcesso(str4,pchTemp);
		arquivoFilhos(str2, word);
		//chamando o filho do processo atual
		func(str2, numProc);
	//}else
	//		break;
	}
	fclose(fp);
	return 0;	
}




int main(){
	char str[100], str2[100], str3[100];
	int numProc = 0;
	printf("|PID     | User          | PROCNAME           | Estado |\n");
	printf("----------------------------------------------------------\n");
	func("/proc/1/task/1/children", &numProc);
	
	
	pid_t pid;
    
    int signo;

    scanf("%d %d",&pid,&signo);

    kill(pid,signo);
	
	
	
	
    return 0;
}
