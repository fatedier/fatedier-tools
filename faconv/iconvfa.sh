#!/bin/env bash

function show_help
{
    echo "Usage:"
    echo "  iconvfa.sh [option] [file|dir]"
    echo -e "  from GB2312 to UTF-8, the old file will be replaced by the new converted file\n"
    echo "Options:"
    echo "  -R: convert files recursively, the following parameter should be the directory name"
}

# param 1: directory name
function convert_rescursive()
{
   local dir_path=`echo $1 | sed 's/\(.*\)\/$/\1/g'`
   local dir_names=`ls ${dir_path} -l | awk '/^d/{print $NF}'`
   
   # convert files in this directory
   local file_names=`ls ${dir_path} -l | awk '/^-/{print $NF}'`
   for file in ${file_names}
   do
       iconv -f ${from_code} -t ${to_code} ${dir_path}/${file} &> /dev/null
       if [ $? == 0 ]; then
           iconv -f ${from_code} -t ${to_code} < ${dir_path}/${file} > $@.$$$$
           cp $@.$$$$ ${dir_path}/${file}
           rm -f $@.$$$$
           echo "File ${dir_path}/${file} is formatted."
       fi
   done

   # if the directory has no other directory, return 0
   if [ "${dir_names}X" == "X" ]; then
       return 0
   fi

   # continue convert files in directories recursively
   for dir in ${dir_names}
   do
       convert_rescursive "${dir_path}/${dir}"
   done 
}

# defines
from_code="GB2312"
to_code="UTF-8"

case "$1" in
"-R")
    ls $2 &> /dev/null
    if [ $? != 0 -o "$2X" == "X" ]; then
        echo "#### error: please check the directory name follow the '-R' option!"
        exit 1
    fi
    convert_rescursive $2
    ;;
"")
    show_help
    ;;
*)
    iconv -f ${from_code} -t ${to_code} $1 &> /dev/null
    if [ $? == 0 ]; then
        iconv -f ${from_code} -t ${to_code} < $1 > $@.$$$$
        cp $@.$$$$ $1
        rm -f $@.$$$$
        echo "File $1 is formatted."
    else
        echo "Convert wrong!"
    fi
    ;;
esac
