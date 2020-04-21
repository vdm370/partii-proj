#! /bin/bash

if [[ $# -ne 3 ]]; then
    echo "Usage: run <programs> <inputs> <K>"
    exit 1
fi

for prog in $1; do
    OUTPUTS=""
    SPACE=""
    N_IN=0
    for K in `seq 1 "$3"`; do
        for input in $2; do
            OUT=$("$prog" < "$input" | tr ' ' '\n' | tail -n 1)
            OUTPUTS="$OUTPUTS$SPACE$OUT"
            SPACE=" "
            N_IN=$((N_IN + 1))
        done
    done

    SUM=$(echo "$OUTPUTS" | tr ' ' + | bc)
    AVG=$(echo "$SUM / $N_IN" | bc -l)
    MIN=$(echo "$OUTPUTS" | tr ' ' '\n' | sort -g | head -n 1)
    echo "$prog $AVG $MIN"
done
