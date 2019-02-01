ruby ru.rb write.txt > write.res
ruby ru.rb read.txt > read.res

gnuplot -persist <<-EOFMarker
 set terminal wxt
set multiplot layout 2,1
 plot "write.res" using 2:1
 plot "read.res" using 2:1
EOFMarker
