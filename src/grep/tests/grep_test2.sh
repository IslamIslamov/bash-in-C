SUCCESS=0
FAIL=0
COUNTER=0
COLOR_REST="$(tput sgr0)"
COLOR_GREEN="$(tput setaf 2)"
COLOR_RED="$(tput setaf 1)"

files=("tests/test_files_2/1.txt" "tests/test_files_2/2.txt" "tests/test_files_2/empty.txt")
template=("python" "print" "main" "home")
flags=("i" "v" "c" "l" "n" "h" "s")

for file1 in "${files[@]}"; do
	for flag1 in "${flags[@]}"; do
		for tem in "${template[@]}"; do
			echo "-$flag1 $tem $file1:"
			./s21_grep "-$flag1" "$tem" "$file1" >s21grep_output.txt
			grep "-$flag1" "$tem" "$file1" >grep_output.txt
			if diff -q s21grep_output.txt grep_output.txt >/dev/null 2>&1; then
				let "COUNTER++"
				let "SUCCESS++"
				echo "$COUNTER - Success"
				printf '%s%s%s%s%s' '[' $COLOR_GREEN '  OK  ' $COLOR_REST '] '
				echo ""

			else
				let "COUNTER++"
				let "FAIL++"
				echo "$COUNTER - Fail"
				printf '%s%s%s%s%s' '[' $COLOR_RED ' FAIL ' $COLOR_REST '] '
				echo ""
			fi

			#valgrind --leak-check=full ./s21_grep "-$flag1" "$tem" "$file1"
		done
	done
done

for flag1 in "${flags[@]}"; do
	for flag2 in "${flags[@]}"; do
		if [[ "$flag1" != "$flag2" ]]; then
			for tem in "${template[@]}"; do
				echo "-$flag1 -$flag2 $tem ${files[0]} ${files[1]} ${files[2]}:"
				./s21_grep "-$flag1" "-$flag2" "$tem" "${files[0]}" "${files[1]}" "${files[2]}" >s21grep_output.txt
				grep "-$flag1" "-$flag2" "$tem" "${files[0]}" "${files[1]}" "${files[2]}" >grep_output.txt
				if diff -q s21grep_output.txt grep_output.txt >/dev/null 2>&1; then
					let "COUNTER++"
					let "SUCCESS++"
					echo "$COUNTER - Success"
					printf '%s%s%s%s%s' '[' $COLOR_GREEN '  OK  ' $COLOR_REST '] '

				else
					let "COUNTER++"
					let "FAIL++"
					echo "$COUNTER - Fail"
					printf '%s%s%s%s%s' '[' $COLOR_RED ' FAIL ' $COLOR_REST '] '
					echo "Your output:"
					cat s21grep_output.txt
					echo "Grep output:"
					cat grep_output.txt
					echo ""
				fi
			done
		fi
	done
done

for flag1 in "${flags[@]}"; do
	for flag2 in "${flags[@]}"; do
		if [[ "$flag1" != "$flag2" ]]; then
			for tem in "${template[@]}"; do
				echo "-$flag1 -$flag2 -e $tem ${files[0]} ${files[1]} ${files[2]}:"
				./s21_grep "-$flag1" "-$flag2" "-e $tem" "${files[0]}" "${files[1]}" "${files[2]}" >s21grep_output.txt
				grep "-$flag1" "-$flag2" "-e $tem" "${files[0]}" "${files[1]}" "${files[2]}" >grep_output.txt
				if diff -q s21grep_output.txt grep_output.txt >/dev/null 2>&1; then
					let "COUNTER++"
					let "SUCCESS++"
					echo "$COUNTER - Success"
					printf '%s%s%s%s%s' '[' $COLOR_GREEN '  OK  ' $COLOR_REST '] '

				else
					let "COUNTER++"
					let "FAIL++"
					echo "$COUNTER - Fail"
					printf '%s%s%s%s%s' '[' $COLOR_RED ' FAIL ' $COLOR_REST '] '

					echo "Your output:"
					cat s21grep_output.txt
					echo "Grep output:"
					cat grep_output.txt
					echo ""
				fi
			done

		fi
	done
done
rm s21grep_output.txt
rm grep_output.txt

printf '%s%s%s%s%s%s' '[' $COLOR_GREEN '  OK:  ' $SUCCESS $COLOR_REST '  ]   '
printf '%s%s%s%s%s%s' '[' $COLOR_RED '  FAILS:  ' $FAIL $COLOR_REST '  ]   '
printf '%s%s%s%s\n' '[' '  TOTAL:  ' $COUNTER '  ]'
