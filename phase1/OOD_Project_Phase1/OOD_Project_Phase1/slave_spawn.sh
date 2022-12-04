#print in red
echo "Starting the master..."
master_exe_path = $1
echo $master_exe_path
eval $master_exe_path
# print in blue
echo "Spawning slaves..."
slave_exe_path = $2

input_dir = $3

for file in $input_dir/slave*.txt
do
    echo "Spawning slave $file"
    eval $slave_exe_path $file &
done