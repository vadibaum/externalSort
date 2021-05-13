echo "Started generation"
./externalSort --blockgenerate $1 $2 190000000 > t$1_$2.txt
echo "Finished generation"
du -h t$1_$2.txt
./externalSort --sort t$1_$2.txt t$1_$2_sorted.txt 10960000
echo "wc run"
wc -lwc t$1_$2.txt
wc -lwc t$1_$2_sorted.txt
echo "sorting by gnu sort"
sort t$1_$2.txt > t$1_$2_sorted.2.txt
wc -lwc t$1_$2_sorted.2.txt
echo "running diffs"
diff t$1_$2_sorted.txt t$1_$2_sorted.2.txt
