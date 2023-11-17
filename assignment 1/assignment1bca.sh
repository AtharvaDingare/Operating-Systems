#!/bin/bash
file_name="gojo.txt"
 
line()
{    
    printf "\n**********************************************\n";
}
 
sline()
{
    printf "\n################################################\n";
}
 
# Function to read address book
read_address_book()
{
    line
 
    echo "Address Book Contain: ";
     
    printf "\n Name \t MobileNo \t Location \n"
    echo "$(cat $file_name)";
 
    line
}
 
# Add Data into Address book
# Primary Key: Mobile Number
add_address_book()
{
    line 
    echo "Please Enter following Details: ";
 
    printf "\n Enter Name:"
    read name
     
    while true
    do
        printf "\n Enter Mobile Number:"
        read mobile_no
         
        pat="^[0-9]{10}$"
        while [[ ! $mobile_no =~ $pat ]]
            do
            printf "\n Please enter correct phone number: "
            read mobile_no
        done
         
        grep $mobile_no $file_name
         
        RETURNSTATUS=`echo $?`
 
        if [ $RETURNSTATUS -eq 0 ]
        then
            echo "Please Enter Another Number"
        else
            break
        fi
 
        unset RETURNSTATUS
        unset mobile_no
    done
     
    printf "\n Enter Location:"
    read location
 
    printf "$name \t $mobile_no \t $location \n"  >> $file_name 
     
    echo "Record Inserted Succeffully"
    line
 
    read_address_book
}
 
# To Read Single Record
read_single()
{
    line
 
    printf "\n Enter Mobile No:"
    read mobile_no
 
    grep $mobile_no $file_name
     
    RETURNSTATUS=`echo $?`
 
    if [ $RETURNSTATUS -eq 1 ]      
    then
        echo "No records found"
    else
        printf "\n\n Records:\n";
        echo "$(grep $mobile_no $file_name)"   
    fi
    line
}
 
# To Update Record in Address Book
update_address_book()
{
    line
 
    printf "\n Enter Mobile Number Search Key:"
    read search_key
 
    grep -n $search_key $file_name
 
    RETURNSTATUS=`echo $?`
 
    if [ $RETURNSTATUS -eq 1 ]      
    then
        echo "No records found for \"$search_key"\"
    else
        printf "\nEnter the line number (the first number of the entry) that you'd like to edit:"
        read lineNumber
        echo
 
        for line in `grep -n "$search_key" $file_name`
        do
            number=`echo "$line" | cut -c1` # cut -c1 = only take first column
            if [ $number -eq $lineNumber ]
            then
                printf "\n Enter Name:";
                read name
                printf "\n Enter Location:";
                read location
 
                edit=`echo -e $name "\t" $search_key "\t $location"`
                 
                lineChange="${lineNumber}s"
                 
                sed -i -e "$lineChange/.*/$edit/" $file_name   
                 
                echo "The change has been made."
            fi
        done 
    fi
    line
    read_address_book
}
 
# To Delete a Single Record
delete_record_address()
{
    line
 
    cat -n $file_name
 
    printf "\n Enter Record Number You Want to Delete:"
    read num
 
    sed -i -e $num"d" $file_name
 
    RETURNSTATUS=`echo $?`
 
    if [ $RETURNSTATUS -eq 1 ]      
    then
        echo "No Such Record Present"
    else
        echo "Record Deleted Successfuly"
    fi
    line
    read_address_book
}
 
# Main Program:
 
sline
 
# Checking File Present or Not
if [ -e $file_name ]
then
    printf "Address Book is Present \n";
else
    printf "Creating a New Address Book \n";
    ch=$(touch $file_name)
    RETURNSTATUS=$(echo $?)
    if [ $RETURNSTATUS -eq  0 ]
    then
        printf "\n New Address Book Created";
    else
        printf "\n Address Book Failed to Create";
    fi
fi
 
while true
do
    sline
    echo " Welcome to AddressBook: ";
    echo " Options: ";
 
    echo " 1) To View Address Book";
    echo " 2) To Add/Insert Address Record";
    echo " 3) To Read/View Single Record";
    echo " 4) To Update/Modify Record";
    echo " 5) To Delete a Record";
    echo " 6) Quit";
 
    printf " Enter a number: ";
    read num
    sline
     
    case $num in
        1) echo "You have selected Read Address Book"
            read_address_book;;
        2) echo "You have selected Add Data into Address Book:"
            add_address_book;;  
        3) echo "You have selected Read Single Record Option"
            read_single;; 
        4) echo "You have selected Update Record "
            update_address_book;;
        5) echo "You have selected Delete a Record "
            delete_record_address;;
        6) echo "Thanks For Using Address Book"
            break;;
        *) echo " Please Select Correct Option";;
    esac
     
    unset num
done