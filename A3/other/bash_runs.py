python2.7 comm.py 
python2.7 comm.py file1
python2.7 comm.py -
python2.7 comm.py - - < file2
python2.7 comm.py dne.txt file1


python2.7 comm.py file1 - < file2 > tmp1
comm file1 - < file2 > tmp2
diff tmp1 tmp2
python2.7 comm.py - file1 < file2 > tmp1
comm - file1 < file2 > tmp2
diff tmp1 tmp2
python2.7 comm.py file1 file2 > tmp1
comm file1 file2 > tmp2
diff tmp1 tmp2
python2.7 comm.py -1 file1 file2 > tmp1
comm -1 file1 file2 > tmp2
diff tmp1 tmp2
python2.7 comm.py -2 file1 file2 > tmp1
comm -2 file1 file2 > tmp2
diff tmp1 tmp2
python2.7 comm.py -3 file1 file2 > tmp1
comm -3 file1 file2 > tmp2
diff tmp1 tmp2
python2.7 comm.py -1 -2 file1 file2 > tmp1
comm -1 -2 file1 file2 > tmp2
diff tmp1 tmp2
python2.7 comm.py -12 file1 file2 > tmp1
comm -12 file1 file2 > tmp2
diff tmp1 tmp2
python2.7 comm.py -1 -2 -3 file1 file2 > tmp1
comm -1 -2 -3 file1 file2 > tmp2
diff tmp1 tmp2
python2.7 comm.py -123 file1 file2 > tmp1
comm -123 file1 file2 > tmp2
diff tmp1 tmp2
python comm.py file5 file6 > tmp1
comm file5 file6 > tmp2
diff tmp1 tmp2
python2.7 comm.py -u uo1 uo2
python2.7 comm.py -u dup1 dup2
python2.7 comm.py dup3 dup4
