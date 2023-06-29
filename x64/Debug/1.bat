1++.exe < 01-example.input.txt > 01-example.actual.txt 2>NUL
fc /N 01-example.actual.txt 01-example.expected.txt || pause