#!/bin/bash

if [ "x$1" == "xbbb" ]; then
	serial=AH01DLUD;
else
	echo "Board not found"
	echo "Usage: switch <board-name> <host|target>"
	exit 1
fi

if [ "x$2" != "xhost" -a "x$2" != "xtarget" ]; then
	echo "Specific host or target"
	echo "Usage: switch <board-name> <host|target>"
	exit 1
fi

echo "Switch board $1 to $2 mode"

sudo switch ${serial} $2
