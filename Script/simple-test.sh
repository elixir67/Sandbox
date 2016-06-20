#!/usr/bin/env bash

TimeCMD=timeout

# Use gtimeout for MacOS
if [ "$(uname)" == "Darwin" ]; then
TimeCMD="gtimeout"
fi

if [[ $# != 4 ]] ; then
echo 'usage: simple-test.sh <host> <clients> <hatch-rate> <minutes>'
echo 'example: simple-test.sh http://localhost:9000 10 1 30>'
exit 1
fi

HOST=$1
echo "Learn host: $HOST"

CLIENTS=$2
echo "Clients: $CLIENTS"

HATCH=$3
echo "Hatch Rate: $HATCH"

CMD="/usr/local/bin/locust -f simple-test.py --host $HOST --clients=$CLIENTS --hatch-rate=$HATCH --no-web --only-summary"

echo "Test Minutes: $4"
Time=$((60*$4))


TotalCMD="$TimeCMD --preserve-status -k 60 $Time $CMD"

echo $TotalCMD

$TotalCMD