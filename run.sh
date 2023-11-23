solution=brute
test_set=tiny_test_set

mkdir -p bin # create bin directory if not exists
rm -f bin/$solution # remove binary of solution if exists
gcc src/$solution/main.c -o bin/$solution # compile solution and generate binary

mkdir -p output # create output directory if not exists
rm -rf output/$test_set # remove existing outputs if they exist
mkdir -p output/$test_set # create output directory if not exists

for test_file in cases/$test_set/*;
do
	test_file=$(basename ${test_file}) # get only file name from full file path
	test_file=${test_file%.*} # remove extension from file name
	echo "Case $test_set/$test_file:"
	input_file=cases/$test_set/$test_file.gr
	solution_file=output/$test_set/$test_file.sol
	./bin/$solution < $input_file > $solution_file
done
