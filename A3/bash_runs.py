python2.7 comm.py 
python2.7 comm.py a.txt
python2.7 comm.py -
python2.7 comm.py - - < b.txt
python2.7 comm.py dne.txt a.txt
python2.7 comm.py a.txt - < b.txt > tmp1
comm a.txt - < b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py - a.txt < b.txt > tmp1
comm - a.txt < b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py a.txt b.txt > tmp1
comm a.txt b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py -1 a.txt b.txt > tmp1
comm -1 a.txt b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py -2 a.txt b.txt > tmp1
comm -2 a.txt b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py -3 a.txt b.txt > tmp1
comm -3 a.txt b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py -1 -2 a.txt b.txt > tmp1
comm -1 -2 a.txt b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py -12 a.txt b.txt > tmp1
comm -12 a.txt b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py -1 -2 -3 a.txt b.txt > tmp1
comm -1 -2 -3 a.txt b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py -123 a.txt b.txt > tmp1
comm -123 a.txt b.txt > tmp2
diff tmp1 tmp2
python2.7 comm.py -u file3 file4