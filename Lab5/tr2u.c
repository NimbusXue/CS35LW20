#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, const char * argv[]) {
    //check the number of arguments
    if(argc!=3){
        fprintf(stderr,"Error: Incorrect number of arguments\n");
        exit(1);
    }
   
    int from_len = strlen(argv[1]);
    int to_len = strlen(argv[2]);
    
    //check the length of from and to
    if(from_len != to_len){
       fprintf(stderr, "Error: From and to are not the same length\n");
       exit(1);
     }
    
    //check whether from has duplicate bytes
    if(from_len>1){
    for(int i=0;i<from_len;i++){
        for(int j=i+1;j<from_len;j++){
            if(argv[1][i]==argv[1][j]){
                fprintf(stderr,"Error: Duplicate bytes in from\n");
                exit(1);
            }
        }
    }
    }
    int c;
    int temp;
    while (temp=read(0, &c, 1)!=0) {
       if(temp==-1)
       {
           fprintf(stderr, "Error: Input failure\n");
           exit(1);
       }
        for(int i=0;i<from_len;i++){
            if(argv[1][i]==c){
                c=argv[2][i];
                break;
            }
        }
        
        if(write(1,&c,1)==-1)
        {
            fprintf(stderr, "Error: Output failure\n");
            exit(1);
        }
    }


    return 0;
       
}
