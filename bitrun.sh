echo "Started generation"
time ./externalSort --blockgenerate $1 $2 > t$1_$2.txt
echo "Finished generation"
du -h t$1_$2.txt
echo "Sorting"
time ./externalSort --sort t$1_$2.txt t$1_$2_sorted.txt 109600000
echo "wc run"
wc -lwc t$1_$2.txt
wc -lwc t$1_$2_sorted.txt
echo "Sorting by gnu sort"
time sort t$1_$2.txt > t$1_$2_sorted.2.txt
wc -lwc t$1_$2_sorted.2.txt
echo "Running diffs"
diff t$1_$2_sorted.txt t$1_$2_sorted.2.txt
rm t$1_$2.txt t$1_$2_sorted.txt t$1_$2_sorted.2.txt
