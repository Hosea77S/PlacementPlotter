# Set the terminal type to x11 for an interactive window
set terminal x11

# Set the range for the plot
set xrange [0:10]
set yrange [0:10]

# Plot a rectangle (block) with a specific border color and fill color
# 'lt' specifies the line type (border color)
# 'fillcolor' specifies the fill color
# 'fillstyle' specifies how the rectangle is filled (e.g., solid)
# 'border' specifies the border width
# 'at' specifies the position of the rectangle
# 'rectangles' tells Gnuplot to plot rectangles
plot '-' using 1:2:3:4:5:6 with boxes lt rgb "blue" fillcolor rgb "light-blue" fillstyle solid border lw 2 
1 5 4 8 "Text in Block 1"
4 7 6 9 "Text in Block 2"
7 5 9 8 "Text in Block 3"
e

# Specify labels for the rectangles
set label "Block 1" at 2.5, 6.5
set label "Block 2" at 5.5, 8
set label "Block 3" at 8, 6.5

# Replot to add labels
replot
