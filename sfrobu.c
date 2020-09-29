#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
 int foption=0;
int frobcmp(char const* a, char const* b){
  if(*a != ' ' && *b == ' ')
     return 1;
  if(*a == ' ' && *b != ' ')
     return -1;
  
  if(foption==0){
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
  }else{
     
      while(*a != ' ' && *b != ' '){
        if(toupper((unsigned char)(*a^42)) < toupper((unsigned char)(*b^42)))
              return -1;
        if(toupper((unsigned char)(*a^42)) > toupper((unsigned char)(*b^42)))
              return 1;
         a++;
         b++;
         if(*a==' ' && *b != ' ')
           return -1;
         if(*a!=' ' && *b == ' ')
           return 1;
       }
  }
  return 0;
}

int compare(const void * a, const void * b){
  return frobcmp(*(char **)a, *(char **)b);
}

void checkoutput(char *data,char **wordlist){
    if (ferror(stdout)) {
       fprintf(stderr, "Error:Output failure\n");
       free(data);
       free(wordlist);
        exit(1);
     }
}

void checkdata(char *data, char *newdata){
  if(newdata == NULL){
        fprintf(stderr,"Error: Memory allocation failure\n");
        free(data);
        exit(1);
  }
}
int main(int argc, char* argv[]){
    char *data = NULL;
    char **wordlist = NULL;
    struct stat buffer;
    int status=fstat(0,&buffer);
    int c;
    int temp;
    int filesize=buffer.st_size;
    int datalen=0;
    int wordlistlen=0;
    if(argc>2){
        fprintf(stderr,"Error: Incorrect number of arguments\n");
        exit(1);
    }
    if(argc == 2 && strcmp(argv[1], "-f") == 0){
        foption=1;
    }else{
        foption=0;
    }
    
    if(argc == 2 && strcmp(argv[1], "-f") != 0){
      fprintf(stderr,"Error: Incorrect option\n");
      exit(1);
    }

    if(status == -1){
           fprintf(stderr,"Error: Input failure\n");
           exit(1);
    }
//   I choose to initially allocate enough memory to hold all the data in that
//   file all at once under the circumstance of standard input being any type
//   of files, including regular file.
//   if(S_ISREG(buffer.st_mode)){
    data=(char*)malloc((filesize)*sizeof(char));
    
    if(data==NULL){
        fprintf(stderr,"Error: Memory allocation failure\n");
        exit(1);
    }
 //   }
   while (temp=read(0, &c, 1)!=0) {
       if(temp==-1)
       {
           fprintf(stderr, "Error: Input failure\n");
           free(data);
           exit(1);
       }
       datalen++;
       if(datalen==filesize){
           filesize=filesize*2;
        char* newdata=(char*)realloc(data, (filesize)*sizeof(char));
           checkdata(data,newdata);
           data=newdata;
       }
       data[datalen-1]=c;
       
       if( data[datalen-1]==' '){
       wordlistlen++;
       }
   }
    if(data[datalen-1]!=' '){
        data[datalen]=' ';
        datalen++;
        wordlistlen++;
    }
    
    wordlist=(char**)malloc((wordlistlen)*sizeof(char*));
    if(wordlist==NULL){
        fprintf(stderr,"Error: Memory allocation failure\n");
        free(data);
        exit(1);
    }
     char* linemember=data;
    int z=0;
    for(int i=0;i<datalen;i++){
        if(data[i]==' '){
            wordlist[z]=linemember;
            linemember=data+i+1;
            z++;
        }
    }
   
     qsort(wordlist,wordlistlen,sizeof(char*),compare);
    char* data2=(char*)malloc((datalen)*sizeof(char));
    if(data2==NULL){
        fprintf(stderr,"Error: Memory allocation failure\n");
               exit(1);
    }
    int g=0;
    for(int i = 0; i < wordlistlen; i++){
       for(int j = 0; wordlist[i][j] != ' '; j++){
           data2[g++]=wordlist[i][j];
       }
        data2[g++]=' ';
   }
    for(int i=0;i<datalen;i++){
         write(1,&(data2[i]),1);
    }
 
    free(data);
    free(wordlist);
    free(data2);
    exit(0);
    
    
}

