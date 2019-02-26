#!/bin/bash

echo "run :- consult('$1'), consult('$2')." > .run.pl
prolog -f .run.pl -g run -t halt

rm .run.pl
