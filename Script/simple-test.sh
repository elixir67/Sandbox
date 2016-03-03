TimeCMD=timeout

# Use gtimeout for MacOS
if [ "$(uname)" == "Darwin" ]; then
    TimeCMD="gtimeout"
fi

if [[ $# -eq 0 ]] ; then
    echo 'usage: simple-test.sh <minutes>'
    exit 1
fi

CMD="/usr/local/bin/locust -f simple-test.py --host http://localhost:9000 --clients=20 --hatch-rate=1 --no-web"

Time=$((60*$1))

TotalCMD="$TimeCMD --preserve-status -k 6 $Time $CMD"

echo $TotalCMD

$TotalCMD