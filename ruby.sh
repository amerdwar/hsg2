ruby ru.rb example.txt > example.res

gnuplot 

gnuplot set terminal wxt

gnuplot plot "example.res" using 2:1
