#!/bin/bash

obj=$(find . -name "*.o" | wc -w)

if [[ $obj -gt 0 ]]; then
    read -p "Objects found! Delete? (y/n): " delete
    if [[ "$delete" = "y" || "$delete" = "Y" ]]; then
        make fclean
    fi
fi

git add .
git status

read -p "Confirm (y/n): " confirm

machine=$(uname -n)
updated_from=""

if echo "$machine" | grep -q "ASUS"; then
	updated_from="Home update"
else
	updated_from="42 update"
fi

if [[ "$confirm" = "y" || "$confirm" = "Y" ]]; then
    timestamp=$(date +"%H:%M:%S %d-%m-%Y")
    message="$updated_from: $timestamp"
    read -p "Add a description to the changes made: " desc
    git commit -m "$message" -m "$desc"
    git push
else
    echo "NOT TODAY!"
fi

