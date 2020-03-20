#!/bin/bash

if [ -f "test" ]; then
	echo "Existe";
	rm test;
else
	echo "No Existe";
	touch test;
fi
