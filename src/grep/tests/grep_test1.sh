#!/bin/bash

flags=("-i" "-v" "-c" "-l" "-n" "-h" "-s")
output_file="grep_output.txt"
s21_output_file="s21_grep_output.txt"

for flag in "${flags[@]}"; do
    grep "$flag" python tests/test_files_1/1.txt tests/test_files_1/2.txt >"$output_file"
    ./s21_grep "$flag" python tests/test_files_1/1.txt tests/test_files_1/2.txt >"$s21_output_file"

    if diff "$output_file" "$s21_output_file" >/dev/null; then
        echo "$flag python tests/test_files_1/1.txt tests/test_files_1/2.txt: Test passed"
    else
        echo "$flag python tests/test_files_1/1.txt tests/test_files_1/2.txt: Test failed"
    fi
done

for ((i = 0; i < ${#flags[@]}; i++)); do
    for ((j = i + 1; j < ${#flags[@]}; j++)); do
        flag1=${flags[i]}
        flag2=${flags[j]}

        grep "$flag1" "$flag2" python tests/test_files_1/1.txt tests/test_files_1/2.txt >"$output_file"
        ./s21_grep "$flag1" "$flag2" python tests/test_files_1/1.txt tests/test_files_1/2.txt >"$s21_output_file"

        if diff "$output_file" "$s21_output_file" >/dev/null; then
            echo "$flag1 $flag2 python tests/test_files_1/1.txt tests/test_files_1/2.txt: Test passed"
        else
            echo "$flag1 $flag2 python tests/test_files_1/1.txt tests/test_files_1/2.txt: Test failed"
        fi
    done
done

for flag in "${flags[@]}"; do
    grep "$flag" -e ["p[a-zA-Z]*n"] tests/test_files_1/1.txt -e ["h[a-zA-Z]*e"] tests/test_files_1/2.txt >"$output_file"
    ./s21_grep "$flag" -e ["p[a-zA-Z]*n"] tests/test_files_1/1.txt -e ["h[a-zA-Z]*e"] tests/test_files_1/2.txt >"$s21_output_file"

    if diff "$output_file" "$s21_output_file" >/dev/null; then
        echo "$flag -e "p[a-zA-Z]*n" tests/test_files_1/1.txt -e "h[a-zA-Z]*e" tests/test_files_1/2.txt : Test passed"
    else
        echo "$flag -e "p[a-zA-Z]*n" tests/test_files_1/1.txt -e "h[a-zA-Z]*e" tests/test_files_1/2.txt : Test failed"
    fi
done

valgrind --leak-check=full ./s21_grep "${flags[@]}" python test_files_1/1.txt test_files_1/2.txt

rm -f "$output_file"
rm -f "$s21_output_file"
