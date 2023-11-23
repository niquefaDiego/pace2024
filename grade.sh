solution=brute
test_set=tiny_test_set

for test_file in cases/$test_set/*;
do
	test_file=$(basename ${test_file}) # get only file name from full file path
	test_file=${test_file%.*} # remove extension from file name
	input_file=cases/$test_set/$test_file.gr
	solution_file=output/$test_set/$test_file.sol
	pace2024verifier $input_file $solution_file
done
