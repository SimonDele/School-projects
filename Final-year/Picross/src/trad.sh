#!/bin/bash
echo ""
lynxfileref=.lynx.log
lynxrequest=.lynxrequest.log
url="https://webpbn.com/export.cgi/webpbn006965"
result=export.cgi
runpl=.run.pl
inputpic=.input.pic
f_solve()
{
	echo $1", t_solve(CLS,CCS)."
}
f_abort_solve()
{
	echo $1", t_abort_solve(CLS,CCS)."
}

translate()
{
 y=$(cat $result |sed '/^\(#.*\)/d')
 y=$(echo $y | sed -e "s/rows/CLS/" | sed -e "s/ cols/, CCS/")
 echo "$y"
}
processVersion()
{
	r=$1
	if [ "$r" = "-r" ] ; then 
		r="-r3" 
	fi
	version=${r:$((-1))}
	plVersion="picross_V$version.pl"
	echo "$plVersion"
}



if [ "$#" -ge 1 ]
then
	 
	if [[ "$1" =~ ^-r[1-3]{0,1}$ ]] ; then
		plVersion=$(processVersion $1)
		if [ $# -gt 1 ] ; then
			echo "$2" > $result
			x=$(translate)
			if [ "$3" = -a ] ; then				
				res=$(f_abort_solve "$x")
			else
				res=$(f_solve "$x")
			fi
			echo "?- "$res > $inputpic
			echo "run :- consult('$plVersion'), consult('$inputpic')." > $runpl
			prolog -f $runpl -g run -t halt
			rm $result  $runpl $inputpic
		else
			echo "Not enought args"
			exit -1
		fi	
	else
		x="$(echo $1 | sed -e 's/\(.\)/key \1_/g')"
		cat $lynxfileref | sed -e "6s/.*/$x/" | sed -e "6s/_/\n/g" | sed -e "/^$/d" > $lynxrequest
		lynx -cmd_script=$lynxrequest $url
	#x=$(cat $result |sed '/^\(#.*\)/d')
	#x=$(echo $x | sed -e "s/rows/CLS/" | sed -e "s/ cols/, CCS/")
		x=$(translate)
		if [ $# -gt 1 ]; then 
			a=1
			if [ "$2" = "-a" -o "$3" = "-a" ] ; then
				res=$(f_abort_solve "$x")
				a=0
			else
				res=$(f_solve "$x") 
			fi

			testRun=$([[ "$2" =~ ^-r[1-3]{0,1}$ ]]; echo $?)
			if [[ "$2" =~ ^-r[1-3]{0,1}$ ]] || [[ "$3" =~ ^-r[1-3]{0,1}$ ]] ; then
				if [ "$testRun" = "0" ] ; then
					r=$2
				else
					r=$3
				fi
				#version=${r:$((-1))}
				#plVersion="picross_V$version.pl"
				plVersion=$(processVersion $r)	
				echo "?- "$res > $inputpic
				echo "run :- consult('$plVersion'), consult('$inputpic')." > $runpl
			#	if [ a = "0" ] ; then
			#		prolog -f $runpl -g run
			#	else
					prolog -f $runpl -g run -t halt
			#	fi
				rm $runpl $inputpic
			else
				echo "$res"
			fi
		else
			f_solve "$x" 
		fi

	rm $lynxrequest $result
	fi
else
	echo "Not enought args"
	exit -1 
fi
