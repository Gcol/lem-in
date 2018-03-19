ant=0
fin=100

while test $ant != $fin
  do
    echo "ants = "$ant
    echo "#ants\n"$ant > $1/model_test
    tail -n 43 $1/model_3 >> $1/model_test
    ./../felix_lemin/lem-in < $1/model_test > fel.txt
    ./../lem-in/lem-in < $1/model_test > you.txt
    ./corrector_lem_in fel.txt > fel1.txt
    ./corrector_lem_in you.txt > you1.txt
	if [[ $? -ne 0 ]]
	then
		exit
	fi
    diff fel1.txt you1.txt
    ant=$(($ant + 1))
done
