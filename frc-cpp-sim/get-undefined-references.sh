#! /bin/sh

make 2>&1 | grep "undefined reference" | sed -r 's/.*undefined reference(.*)/undefined reference\1/' | sort | uniq > undefined-references
echo "`cat undefined-references | wc -l` unique undefined references"
