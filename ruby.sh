ruby ru.rb example.txt > example.res

gnuplot 

set terminal wxt

plot "example.res" using 2:1
