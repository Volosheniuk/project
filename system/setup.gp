#!/usr/bin/gnuplot -persist
#
#
# This is gnuplot script
# Symbol '#' start a one line comment (just like '//' in C)
#
# There some style setting you're free to change
# But please be sure you have a copy of this file before rewrite it
#
#
#
# 
# Output format. Choose any you like.
#
	#set terminal postscript
	#set output "./out.eps"
#
	#set terminal jpeg
	#set output "./out.jpeg"
#	
#
#
	set border 3 front linewidth 1.5
#
	unset label
	unset xlabel
	unset ylabel
#
#
	set xtics mirror
	set ytics mirror
#

#
	set angles radians
	#set angles degrees
#
# Separator of data in your input file
	#set datafile separator ","
	#set datafile separator whitespace
#

	set xrange [ 0.0 : * ] noreverse nowriteback
	set yrange [ 0.0 : * ] noreverse nowriteback

#    EOF
