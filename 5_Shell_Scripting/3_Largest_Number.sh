. #!/bin/bash 
 
echo -n "How many numbers? " 
read n 
 
echo "Enter $n numbers:" 
for ((i = 0; i < n; i++)) 
do 
    read num 
    nums[i]=$num 
done 
 
# Initialize largest with the first 
element 
largest=${nums[0]} 
 
for i in "${nums[@]}" 
do 
    if [ $i -gt $largest ]; then 
        largest=$i 
    fi 
done 
 
echo "Largest number is $largest"