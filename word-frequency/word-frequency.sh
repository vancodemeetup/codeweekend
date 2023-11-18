#!/bin/bash

tr -s '[:space:]\n' '\n' < words.txt | sort | uniq -c | sort -n -r -k1 | awk '{print $2 " " $1}'
