#! /bin/sh

# Generate all possible combinations of 1, 2 and 3

echo "Possible combinations 1,2,3 (with repitions):"
for i in 1 2 3
do
    for j in 1 2 3
    do
        for k in 1 2 3
        do
            echo "$i$j$k"
        done
    done
done

