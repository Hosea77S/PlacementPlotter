
set title "name = myfulladder_tmpdir/myfulladder_final #Cells: 25 #Nets: 34" font "Times, 22"
set size ratio 1
set nokey

plot[:][:] '-' w l lt 3

# Border
0, 0
0, 1000
1000, 1000
1000, 0
0, 0

EOF

set object rect from 50, 100 to 350, 500 fs empty border lc rgb '#008800' lw 2
set label "Block 1" at 100, 450

set object rect from 90, 200 to 0, 0
set label "Block 2" at 140, 150

set arrow from -20, -22 to 800, 800 lt rgb 'green' lw 1
set label "n14" at 400, 400 tc rgb 'green' font 'Times, 12' 

replot

pause -1 'Press any key to close.'

