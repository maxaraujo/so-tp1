 /* print files in current directory in reverse order */
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

int func(char *str, int espaco) 
{
	int c, a;	
	FILE *fp;
	char *pch, line[1000], str2[100], pchTemp[100];
	strcpy(str2,"");
	strcpy(pchTemp,"");
	fp = fopen (str,"r");	
	if (fp == NULL){
		printf ("entrei \n");
		return 0;
	}
	else{
		while (fgets(line, sizeof(line), fp)) {        
		 	pch = strtok (line," ");
			 while (pch != NULL)
			  {
			    //for(a=0; a<espaco; a++){
				//strcat(pchTemp, "\t");
			    //}
			    //strcat(pchTemp, pch);
			    //printf ("%s\n",pchTemp);
			    printf ("%s\n",pch);
			    strcpy(str2, "/proc/");			
			    strcat(str2, pch);
			    strcat(str2, "/task/");	
			    strcat(str2, pch);
			    strcat(str2, "/children");
			    printf ("%s\n",str2);
			    func(str2, espaco+1);
			    pch = strtok (NULL, " ");
		  }
    	}
	//fclose(fp);
	return 0;
	}
}

main(){

func("/proc/1/task/1/children", 0);

} 
