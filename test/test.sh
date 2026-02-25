#!/bin/bash

APP="./app"
OUTPUT="out.txt"
STUDENT_FILE="../data/data"

echo "🔨 Building..."
gcc -Wall -Wextra -std=c11 \
    ../src/main.c ../src/student.c \
    -I../include -o "../app"

if [ $? -ne 0 ]; then
    echo "❌ Build failed"
    exit 1
fi

echo "🚀 Running tests..."
for input in input*.txt; do
    name=${input%.txt}             # input_delete
    suffix=${name#input_}          # delete

    expected="expected_${suffix}.txt"
    data="data_${suffix}"

    echo "----------------------------------"
    echo "Running test: $suffix"

    # 🔹 Reset database
    if [ -f "$data" ]; then
        cp "$data" "$STUDENT_FILE"
    else
        rm -f "$STUDENT_FILE"
    fi
    
    cd ..

    "$APP" < "test/$input" > "test/${suffix}_${OUTPUT}"

    cd test

    # 🔹 Compare output
    if diff -q "$expected" "${suffix}_${OUTPUT}" > /dev/null; then
        echo "✅ Test $suffix PASSED"
        rm -f "${suffix}_${OUTPUT}"
    else
        echo "❌ Test $suffix FAILED"
        diff -u "$expected" "${suffix}_${OUTPUT}"
    fi


done

echo "Done."