set terminal wxt
set title 'Assignment A'
plot         'A1.txt' with lines lw 1 title 'n=6',        'A2.txt' with lines lw 1 title 'n=11',        'A3.txt' with lines lw 1 title 'n=21',        'A4.txt' with lines lw 1 title 'n=41',		'A5.txt' with lines lw 1 title 'n=81',           1/(1+25*x*x) with points pointtype 3 pointsize 0.5 title 'f(x)'
