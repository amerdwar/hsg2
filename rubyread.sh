ruby ru.rb read.txt > read.res

gnuplot 

gnuplot set terminal wxt

gnuplot plot "read.res" using 2:1
