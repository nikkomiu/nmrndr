#!/bin/sh

# Directory containing the .info files
search_directory="Build/coverage"

# Output merged .info file
output_info_file="Build/coverage/merged.info"

# Coverage output directory
coverage_output_directory="Build/coverage/html"

# Find all .info files and store their paths in an array
info_files=()
while IFS= read -r -d '' file; do
    info_files+=("$file")
done < <(find "$search_directory" -name "*.info" -print0)

# Generate the lcov merge command
merge_command="lcov"
for info_file in "${info_files[@]}"; do
    merge_command+=" --add-tracefile $info_file"
done
merge_command+=" --output-file $output_info_file"

# Execute the merge command
eval "$merge_command"

# Generate HTML coverage report
genhtml "$output_info_file" --output-directory $coverage_output_directory

echo "Coverage report merged and generated in $coverage_output_directory directory."
