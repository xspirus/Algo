# !/bin/bash

executable=$1
testCaseDir=$2
numberOfTestCases=$3

for i in `seq 1 $numberOfTestCases`;
	do
		startT=$(date +%s%N)
		result=$(./$executable < $testCaseDir/input$i.txt)
		endT=$(date +%s%N)
		expected=$(cat $testCaseDir/output$i.txt | tr -d '\r')
		if [ "$result" = "$expected" ]
		then
			echo "Testcase #$i passed!"
		else
			echo "Testcase #$i failed to pass!"
			#echo -e "Output:\n$result"
			#echo -e "Expected output:\n$expected"
		fi
		runtime=$(((endT-startT)/1000000))
		echo -e "Execution time\t: $runtime ms"
		echo
	done
