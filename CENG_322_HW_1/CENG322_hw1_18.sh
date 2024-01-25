#!/bin/bash

# 270201072 Gökay Gülsoy
# 270201071 Merve Nur Ozan


# first function
rename_and_copy_to_Found()
{

  mkdir Found
  cd Found
  found_dir=`pwd`
  cd ..
  flag=0
  init_dir=`pwd`
  touch original_modification_details.txt
  org_modf_file_name=`basename original_modification_details.txt`
  cd $1
  
  # Recursively searching for files
  for file in `grep -rl $2`
  do
  
     if [ -f "$file" ]
     then
        
        flag=$((flag+1))
    
        found_txt="found_"
        file_name=`basename $file`
        file_path=`dirname $file`
        modification_date=`date -r "$file_path/$file_name" +"%B %d, %Y at %H.%M."`
        modified_person=`stat --printf="%U" "$file_path/$file_name"`
        found_txt+="$file_name"
        echo "File $flag: $found_txt was modified by $modified_person on $modification_date" >> "$init_dir/$org_modf_file_name"
        cd $file_path
        #rename the file
        mv $file_name $found_txt 
        full_path="`pwd`/$found_txt"
        # copying file to Found Directory
        cp $full_path $found_dir
        cd "$init_dir/$1"
            
     fi     
  done
  
  
  if [ "$flag" -ne 0 ]
  then
      echo -e "\nFiles were copied to the Found directory!\n"
      cd $found_dir
      echo "Files in Found directory"
      # Displaying files on the Found directory
      for file in `ls`
      do
        echo "$file"
      done  
      touch modification_details.txt
      echo ""
      cd $init_dir
  else
      echo -e "\nKeyword not found in files!\n"
      rm -d $found_dir
      rm "$init_dir/$org_modf_file_name"
  fi 
  
  return $flag
}


# Second function
display_modification_details_and_write_output()
{
    cd $found_dir
    
    while read line
    do 
      echo "$line"
      echo "$line" >> modification_details.txt
    done < "$init_dir/$org_modf_file_name"   
    
    rm "$init_dir/$org_modf_file_name"
}


	
echo -n "Enter the name of the directory: "
read DIR_NAME
echo -ne "\nEnter the keyword: "
read KEY_WORD


if [ -d "$DIR_NAME" ]
then 
 
    if [ "$KEY_WORD" = "" ]
    then
       echo -e "\nKeyword cannot be empty!\n"  
              
    else  
       rename_and_copy_to_Found $DIR_NAME $KEY_WORD

       isFound=$?
       if [ $isFound -ge 1 ]
       then
         display_modification_details_and_write_output
       fi  
    fi
else 
   echo -e "\nDirectory does not exist!\n"
fi
   
