make > /dev/null
EXEC=./philo_bonus

if [ "0" != $(echo $?) ]; then
	exit
fi

if [[ -z "$@" ]]; then
	# 4 500 200 200
	# 5 800 200 200
	$EXEC 5 800 200 200
else
	$EXEC $@
fi
