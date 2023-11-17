opt=1
fileName=""
cont=1

while [ "$opt" -lt 6 ]
do
	echo -e "Choose one of the Following\n1. Create a New Address Book\n2. View Records\n3. Insert new Record\n4. Delete a Record\n5. Modify a Record\n6. Exit\nEnter the choice:"
	read opt
	case $opt in
	1)
		echo "Enter filename"
		read fileName
		if [ -e "$fileName" ]; then
			rm "$fileName"
		fi
		echo -e "NAME\tNUMBER\t\tADDRESS\n===============================\n" > "$fileName"
		while [ "$cont" -gt 0 ]
		do
			echo "Enter Name : "
			read name
			echo "Enter Phone Number of $name : "
			read number
			echo "Enter Address of $name  : "
			read address
			echo -e "$name\t$number\t\t$address" >> "$fileName"
			echo "Enter 0 to Stop, 1 to Enter next"
			read cont
		done
		;;
	2)
		if [ -z "$fileName" ]; then
			echo "No Address Book created yet."
		else
			cat "$fileName"
		fi
		;;
	3)
		if [ -z "$fileName" ]; then
			echo "No Address Book created yet. Please create one first."
		else
			echo "Enter Name : "
			read name
			echo "Enter Phone Number of $name : "
			read number
			echo "Enter Address of $name : "
			read address
			echo -e "$name\t$number\t\t$address" >> "$fileName"
		fi
		;;
	4)
		if [ -z "$fileName" ]; then
			echo "No Address Book created yet. Please create one first."
		else
			echo -e "Delete record\nEnter Name/Phone Number : "
			read pattern
			temp="temp"
			grep -v "$pattern" "$fileName" > "$temp"
			mv "$temp" "$fileName"
		fi
		;;
	5)
		if [ -z "$fileName" ]; then
			echo "No Address Book created yet. Please create one first."
		else
			echo -e "Modify record\nEnter Name/Phone Number : "
			read pattern
			temp="temp"
			grep -v "$pattern" "$fileName" > "$temp"
			mv "$temp" "$fileName"
			echo "Enter Name : "
			read name
			echo "Enter Phone Number of $name : "
			read number
			echo "Enter Address of $name : "
			read address
			echo -e "$name\t$number\t\t$address" >> "$fileName"
		fi
		;;
	esac
done
