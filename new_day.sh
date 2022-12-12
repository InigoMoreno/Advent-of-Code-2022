#!/bin/bash

# exit when any command fails
set -e

DAY=${1:-$(date +%-d)}
YEAR=${2:-$(date +%Y)}

if [[ ! -f "src/day${DAY}.cpp" ]]; then
    sed "s/0/${DAY}/g" src/day0.cpp >"src/day${DAY}.cpp"
fi

if [[ ! -f "input/input${DAY}.txt" ]]; then
    aocdl -output "input/input${DAY}.txt" -day "${DAY}" -year "${YEAR}"
fi

if [[ ! -f "input/input${DAY}-example.txt" ]]; then
    curl --silent "https://adventofcode.com/${YEAR}/day/${DAY}" | xmllint --html --xpath "(//p[contains(., 'example')])[1]/following-sibling::pre[1]/code/text()" - > "input/input${DAY}-example.txt"
fi

xdg-open "https://adventofcode.com/${YEAR}/day/${DAY}"

code "src/day${DAY}.cpp"
