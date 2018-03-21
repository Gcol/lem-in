echo "ant ="$3
echo "#ants\n"$3 > $1/model_test
tail -n +2 $1/$2 >> $1/model_test
./../lem_in/lem-in < $1/model_test > fel.txt;
./../vsporer/lem-in < $1/model_test > you.txt;
./corrector_lem_in_full fel.txt you.txt;
