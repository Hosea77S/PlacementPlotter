set terminal pngcairo enhanced
set output 'blocks.png'
set size ratio -1
set xrange [0:1000]
set yrange [0:1000]
set object rect from 27, 54 to 527, 654 fc rgb 'blue' fill solid border lc rgb 'black' lw 1
set object rect from 5, 90 to 605, 111 fc rgb 'blue' fill solid border lc rgb 'black' lw 1
plot NaN notitle
