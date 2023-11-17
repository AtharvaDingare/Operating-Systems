filename="gojo.txt"

line()
{
	printf "\n*************************************\n"
}

sline()
{
	printf "\n###############################################\n"
}


read_address_book()
{
	printf "\nThe entire address book is listed below \n"
	
	printf "\n NAME \t mobile_number \t location \t \n"
	echo "$(cat $filename)";
	
	line
}


add_record()
{
	line
	printf "Enter your name : \n"
	read name
	
	while true
	do
		printf "Enter your mobile number\n"
		read mobile_no
		
		pat="^[0-9]{10}$"
		while [[ ! $mobile_no =~ $pat ]]
		do
			printf "Mobile number should contain 10 digits from [0-9] \n"
			read mobile_no
		done
		
		grep $mobile_no $filename

		RETURNSTATUS=`echo $?`
		
		if [ $RETURNSTATUS -eq 0 ]
		then
			printf "Given mobile number is already registered , validate\n"
		else
			break
        fi

	done
	
	printf "Enter your location\n"
	read location
	
	printf "\n $name \t $mobile_no \t $location \t \n" >> $filename
	
	printf "Entry successfully recorded! \n"
	
	read_address_book
	
	sline
	
	unset RETURNSTATUS
	unset mobile_no
	
}

single_record()
{
	printf "Enter the mobile number you want to search\n"
	read mobile_no
	
	grep $mobile_no $filename
	RETURNSTATUS=`echo $?`
	
	if [ $RETURNSTATUS -eq 0 ]
	then
		printf "Record with mobile number : $mobile_no found! \n"
		echo $(grep $mobile_no $filename)
	else
		printf "Record not found ! \n"
	fi
	
	sline
	
	unset RETURNSTATUS
	unset mobile_no
}

update_record()
{
	line
}

delete_record()
{
	line
}






# main program

sline

# logic to verify if address book is present , and if not , create such an address book

if [ -e $filename ]
then
	printf "\nAddress Book with given name found\n"
else
	printf "\n Address Book with given name was not found\n"
	printf "\nCreating address book\n"
	ch=$(touch $filename) # creates a file with given filename
	RETURNSTATUS=`echo $?` # checks if the previous command executed correctly
	if [ $RETURNSTATUS -eq 0 ]
	then 
		printf "\nNew Address book created\n"
	else
		printf "\n Failed to create address book\n"
	fi
fi


# actual logic after creation of address book (menu driven)

while true
do
	sline
	
	printf "\n***** Welcome to the address book *****\n"
	printf "1) View Address book\n"
	printf "2) Add record to address book\n"
	printf "3) Read single record from address book\n"
	printf "4) Update record from address book\n"
	printf "5) Delete record from address book\n"
	printf "6) Exit\n"
	
	echo "Enter a choice : "
	read option
	
	case $option in
		1) echo "You have selected to view address book\n"
			read_address_book
            ;;
		2) echo "You have selected to add record into address book\n"
			add_record
            ;;
		3) echo "You have selected to read a single record of address book\n"
			single_record
            ;;
		4) echo "You have selected to update record from address book\n"
			update_record
            ;;
		5) echo "You have selected to delete record from address book\n"
			delete_record
            ;;
		6) echo "Exiting address book"
			break
            ;;
		*) echo "Please enter a valid choice"
            ;;
	esac

    unset option
	
done
