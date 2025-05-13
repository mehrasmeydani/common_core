run_funcheck="funcheck"
run_solong="./so_long"
for filename in ./invalid_maps/*; do 
cat "$filename" | tr 'p' 'P' | tr 'c' 'C' | tr 'e' 'E' > "$filename"
#"$run_funcheck" "$run_solong" "$filename"
done