run_funcheck="funcheck"
run_solong="./so_long"
for filename in ./invalid_maps/*; do 
"$run_solong" "$filename"
done