filename=$1
n_small=$2
n_med=$3

if [ -z "$filename" ] ; then
	echo "to run tests"
	echo "usage: ./test.sh compiled"
 	echo
 	echo "to create tests"
 	echo "usage: ./test.sh compiled n_small n_medium"
 	echo
 	echo -e "\e[31mWARNING\e[0m creating tests will delete all previous tests"
 	exit 0
fi


if [ -z "$n_small" ] ; then
	for test in tests/* ; do
		max=$(./$filename < $test)


		file=${test#"tests"}

		res=$(diff <(echo $max) <(cat res$file))

		if ! [ -z "$res" ] ; then
			echo found diffrence in tests/$file
			echo correct v    wrong v
			echo $res
		fi 

		
	done
	exit 0
fi

if [ -z "$n_small" ] ; then
	exit 0
fi


echo "removing"
rm -f tests/small_* tests/med_* res/small_* res/med_*


for ((i=1;i<=n_small;i++)) ; do
	python2.7 p2_gerador.py -n 10 -N 10 -m 10 -M 10 -s 5 -S 5 -c 5 -C 5 > tests/small_$i
	max=$(./$filename < tests/small_$i)
	echo "$max" > res/small_$[i]
done

for ((i=1;i<=n_med;i++)) ; do
	python2.7 p2_gerador.py -n 100 -N 100 -m 100 -M 100 -s 300 -S 300 -c 300 -C 300  > tests/med_$i
	max=$(./$filename < tests/med_$i)
	echo "$max" > res/med_$[i]
done
