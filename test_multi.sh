ant=1
fin=100

rm -rf error
mkdir error
for i in `find $1 -type f`
do
	ant=1
	echo "file =" $i
	ferror=error/`basename $i`
	mkdir $ferror
	while test $ant != $fin
	do
		echo "#ants\n"$ant > model_test
		tail -n +2 $i >> model_test
		./../felix_lemin/lem-in < model_test > fel.txt
		./../lem-in/lem-in < model_test > you.txt
		./corrector_lem_in fel.txt > fel1.txt
		./corrector_lem_in you.txt > you1.txt
		diff fel1.txt you1.txt > /dev/null
		if [[ $? -ne 0 ]]
		then
			if [[ `head -n 1 you1.txt` -gt `head -n 1 fel1.txt` ]]
			then
				state="worstest"
			else
				state="bestest"
			fi
			cat you.txt >> "$ferror/$ant($state)"
			cat fel.txt >> "$ferror/$ant($state)"
			diff fel1.txt you1.txt >> "$ferror/$ant($state)"
		fi
		ant=$(($ant + 1))
	done
done
