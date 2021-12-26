EXEC=./philo

# TESTS:
# 5 800 200 200 (no die)
# 5 800 200 200 7 (finish)
# 4 410 200 200 (no die)
# 4 310 200 200 (dies)

make > /dev/null

if [ "0" != $(echo $?) ]; then
	exit
fi

if [[ -z "$@" ]]; then
	# 4 500 200 200
	# 5 800 200 200
	$EXEC 4 410 200 200
else
	$EXEC $@
fi
