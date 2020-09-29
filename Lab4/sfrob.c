#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int frobcmp(char const* a, char const* b){
  if(*a != ' ' && *b == ' ')
     return 1;
  if(*a == ' ' && *b != ' ')
     return -1;
     
  while(*a != ' ' && *b != ' '){
    if((*a^42) < (*b^42))
      return -1;
    if((*a^42) > (*b^42))
      return 1;
    a++;
    b++;
    if(*a==' ' && *b != ' ')
      return -1;
    if(*a!=' ' && *b == ' ')
      return 1;
  }
  return 0;
}

int compare(const void * a, const void * b){
  return frobcmp(*(char **)a, *(char **)b); 
}

void freelines(char **lines, char*line, int lines_len){
  free(line);
  for(int i=0;i<lines_len;i++){
    free(lines[i]);
  }
  free(lines);
}

void checkline(char *line, char *newline,char **lines,int lines_len){
  if(newline == NULL){
        fprintf(stderr,"Error: Memory allocation failure");
        freelines(lines,line,lines_len);
        exit(1);
  }
}

void checklines(char **lines, char **newlines, char*line, int lines_len){
  if(newlines == NULL){
        fprintf(stderr,"Error: Memory allocation failure");
        freelines(lines,line,lines_len);
        exit(1);
  }
}
int main(){
  int c;
  char *newline;
  char **newlines;
  char *line = NULL;
  char **lines =NULL;
  int line_len = 0;
  int lines_len = 0;
 
  while ((c = getchar()) != EOF) {
    if(c!=' '){
      line_len++;
   
      newline = (char*)realloc(line, (line_len)*sizeof(char));
      checkline(line,newline,lines,lines_len);
      line=newline;
      
        line[line_len-1]=c;
 
    }else{
      lines_len++;
      newlines = (char**)realloc(lines, (lines_len)*sizeof(char*));
      checklines(lines,newlines,line,lines_len-1);
      lines=newlines;

	newline = (char*)realloc(line, (line_len+1)*sizeof(char));
	checkline(line,newline,lines,lines_len-1);
	line=newline;

	line[line_len] = ' ';

	lines[lines_len-1] = line;
	line = NULL;
	line_len = 0;
	 
      
    }
      
  }

  if (feof(stdin)) {
    if(lines_len == 0 || line_len > 0){
      newline = (char*)realloc(line, (line_len+1)*sizeof(char));
      checkline(line,newline,lines,lines_len);
      line=newline;

        line[line_len]=' ';
	newlines = (char**)realloc(lines, (lines_len+1)*sizeof(char*));
	checklines(lines,newlines,line,lines_len);
	  lines=newlines;

	lines[lines_len]=line;
	line=NULL;
	lines_len++;
    }
  } else if (ferror(stdin)) {
    fprintf(stderr, "Error:Input failure");
    freelines(lines,line,lines_len);
     exit(1);
  } else {
    fprintf(stderr,"Error: Received a character that resembles EOF");
    freelines(lines,line,lines_len);
    exit(1);     
  }
    
  qsort(lines,lines_len,sizeof(char*),compare);
    for(int i = 0; i < lines_len; i++){
      for(int j = 0; lines[i][j] != ' '; j++){
        putchar(lines[i][j]);
      }
       printf(" ");
  }
  
    if (ferror(stdout)) {
    fprintf(stderr, "Error:Output failure");
    freelines(lines,line,lines_len);
     exit(1);
  }
    freelines(lines,line,lines_len);
    exit(0);
        
}




