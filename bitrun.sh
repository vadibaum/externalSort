echo "Started generation"
./externalSort --bitgenerate $1 $2 > t$1_$2.txt
echo "Finished generation"
./externalSort --sort t$1_$2.txt t$1_$2_sorted.txt 10960000
wc -lwc t$1_$2.txt
wc -lwc t$1_$2_sorted.txt
sort t$1_$2.txt > t$1_$2_sorted.2.txt
wc -lwc t$1_$2_sorted.2.txt
diff t$1_$2_sorted.txt t$1_$2_sorted.2.txt
