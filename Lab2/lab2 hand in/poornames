#! /bin/bash

function poorname(){
   local D=$1

   IFS=$'\n'
if [ -d $D ];then
    #remove the trailing / if it exists
    D=`echo $D | sed 's/\/$//g'`
    cd $D
    #grep the file contain char other than ASCII letters, ‘.’, ‘-’, and ‘_’
    ls -1 -a  | grep -E "[^-_\.a-zA-Z]" >> ~/filename
   
    #grep the file with more than 14 characters
    ls -1 -a | grep -E -v '^.{1,14}$' >> ~/filename
   
    #grep leading -
    ls -1 -a | grep -E '^-.*$'>> ~/filename
    
    #grep everyleading dot except . and ..
    ls -1 -a |  grep -E '^\..*$'|grep -Ev '^\.$'|grep -Ev '^\.\.$'>> ~/filename
    
    # find all the duplicate case insensitive
    ls -1 -a |sort -u|sort -f|uniq -iD>> ~/filename
     
     #sort to remove duplicates and append / to every line and then append $D
    value=`sort -u < ~/filename`
 
    
   set -f
     for file in $value
do
    if [ -d "$file" ]
    then
    echo  "$D"/"$file"/
    
    else
    echo "$D"/"$file"
    
    fi
done
     rm ~/filename
fi
          
find $D -maxdepth 1 -mindepth 1 -type d -exec basename {} \;|
    while read -r dnames       
        do
            poorname "$D/$dnames"
       done

}
if [[ "$1" == "-r" ]];then
        D2=$2
        if [ "$#"  -eq  1 ];then
            D2="$(pwd -P)"
        fi

        if [[ "$2" == "." ]];then
            D2="$(pwd -P)"
	    
	fi

        if [ "$#" -gt 2 ];then
            echo "Error: there are two or more operands" 1>&2
            exit 1
        fi


        if [[ $D2 =~ ^- ]];then
            echo "Error: first chracter cannot start with '-'" 1>&2
            exit 1
        fi

        if [ ! -d $D2 ];then
            echo "Error: this is not the name of a diretory" 1>&2
            exit 1
        fi


        if [ -L $D2 ];then
            echo "Error: this is a symbolic link" 1>&2
            exit 1
        fi

        if [ ! -r $D2 ];then
            echo "Error: lack of permissions to read the directory" 1>&2
        fi
           poorname $D2


else

        D3=$1
        if [[ $D3 =~ ^- ]];then
            echo "Error: first chracter cannot start with '-'" 1>&2
            exit 1
        fi

        if [ "$#" -gt 1 ];then
            echo "Error: there are two or more operands" 1>&2
            exit 1
        fi


        if [ ! -d $D3 ];then
            echo "Error: this is not the name of a diretory" 1>&2
            exit 1
        fi

        if [ "$#"  -eq  0 ];then
            D3="."
        fi

        if [ -L $D3 ];then
            echo "Error: this is a symbolic link" 1>&2
            exit 1
        fi

        if [ ! -r $D3 ];then
            echo "Error: lack of permissions to read the directory" 1>&2
        fi

           IFS=$'\n'
        if [ -d $D3 ];then
            #remove the trailing / if it exists
            D=`echo $D | sed 's/\/$//g'`
            cd $D3
            #grep the file contain char other than
	    #ASCII letters, ‘.’, ‘-’, and ‘_’
            ls -1 -a  | grep -E "[^-_\.a-zA-Z]" >> ~/filename
           
            #grep the file with more than 14 characters
            ls -1 -a | grep -E -v '^.{1,14}$' >> ~/filename
           
            #grep leading -
            ls -1 -a | grep -E '^-.*$'>> ~/filename
            
            #grep everyleading dot except . and ..
            ls -1 -a |  grep -E '^\..*$'|
	    grep -Ev '^\.$'|grep -Ev '^\.\.$'>> ~/filename
            
            # find all the duplicate case insensitive
            ls -1 -a |sort -u|sort -f|uniq -iD>> ~/filename
             
            #sort to remove duplicates and append / to every line
	    #and then append $D
            value=`sort -u < ~/filename`
            set -f
             for file in $value
        do
            if [ -d "$file" ]
            then
            echo  "$D3"/"$file"/
            
            else
            echo "$D3"/"$file"
            
            fi
        done
             rm ~/filename
          
          
        fi
fi
