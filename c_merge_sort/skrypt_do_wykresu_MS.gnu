set term pngcairo lw 1.0 font ",28" size 1536,998 #png
##set term svg #svg
set output "output.png" #png
##set output "output.svg" #svg
set size ratio 0.65 0.95,0.95
set xlabel "{/:Bold n[-]}" right offset 24.5,0.8
set ylabel "{/:Bold t[ms]}" right rotate by 0  offset 4,7
set encoding utf8
set title "{/:Bold Merge Sort}"
set key left top
plot "wyniki_sortowania_MS.txt" u 1:2 w lines title "losowe", "wyniki_sortowania_MS.txt" u 1:3 w lines title "rosnące", "wyniki_sortowania_MS.txt" u 1:4 w lines title "malejące", "wyniki_sortowania_MS.txt" u 1:5 w lines title "stałe", "wyniki_sortowania_MS.txt" u 1:6 w lines title "V"
