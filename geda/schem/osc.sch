v 20130925 2
C 44200 43000 0 0 0 title-A4.sym
C 45400 47900 1 90 0 resistor-1.sym
{
T 45000 48200 5 10 0 0 90 0 1
device=RESISTOR
T 45700 48700 5 10 1 1 180 0 1
refdes=R1
T 45400 47900 5 10 0 0 0 0 1
footprint=R025
}
C 45400 46400 1 90 0 resistor-1.sym
{
T 45000 46700 5 10 0 0 90 0 1
device=RESISTOR
T 45700 47100 5 10 1 1 180 0 1
refdes=R2
T 45400 46400 5 10 0 0 0 0 1
footprint=R025
}
C 50100 48900 1 270 0 resistor-1.sym
{
T 50500 48600 5 10 0 0 270 0 1
device=RESISTOR
T 50400 48600 5 10 1 1 0 0 1
refdes=R3
T 50100 48900 5 10 0 0 0 0 1
footprint=R025
}
C 50100 47500 1 270 0 resistor-1.sym
{
T 50500 47200 5 10 0 0 270 0 1
device=RESISTOR
T 50400 47200 5 10 1 1 0 0 1
refdes=R4
T 50100 47500 5 10 0 0 0 0 1
footprint=R025
}
C 46500 46400 1 0 0 capacitor-1.sym
{
T 46700 47100 5 10 0 0 0 0 1
device=CAPACITOR
T 46700 46900 5 10 1 1 0 0 1
refdes=C1
T 46700 47300 5 10 0 0 0 0 1
symversion=0.1
T 46500 46400 5 10 0 0 0 0 1
footprint=CK06_type_capacitor
}
C 47800 46400 1 0 0 capacitor-1.sym
{
T 48000 47100 5 10 0 0 0 0 1
device=CAPACITOR
T 48000 46900 5 10 1 1 0 0 1
refdes=C2
T 48000 47300 5 10 0 0 0 0 1
symversion=0.1
T 47800 46400 5 10 0 0 0 0 1
footprint=CK06_type_capacitor
}
C 47600 45600 1 0 0 inductor-1.sym
{
T 47800 46100 5 10 0 0 0 0 1
device=INDUCTOR
T 47800 45900 5 10 1 1 0 0 1
refdes=L1
T 47800 46300 5 10 0 0 0 0 1
symversion=0.1
T 47600 45600 5 10 0 0 0 0 1
footprint=RADIAL_CAN 300
}
N 48700 46600 48700 45700 4
N 48700 45700 48500 45700 4
N 47800 46600 47400 46600 4
N 49800 47800 50200 47800 4
N 50200 47500 50200 48000 4
N 50200 46600 48700 46600 4
N 46500 44600 46500 48000 4
N 47600 46600 47600 47600 4
N 45300 47600 48800 47600 4
N 46500 48000 48800 48000 4
C 45200 45600 1 0 0 gnd-1.sym
C 45100 49100 1 0 0 5V-plus-1.sym
N 45300 49100 45300 48800 4
N 45300 47900 45300 47300 4
N 45300 46400 45300 45900 4
C 50000 49100 1 0 0 5V-plus-1.sym
N 50200 48900 50200 49100 4
C 46700 50600 1 0 0 5V-plus-1.sym
C 49500 48400 1 0 0 gnd-1.sym
N 49300 48100 49300 48700 4
N 49300 48700 49600 48700 4
C 48800 48200 1 180 1 lm311.sym
{
T 48925 44800 5 8 0 0 180 6 1
device=comparator
T 48900 46000 5 8 0 0 180 6 1
symversion=1.0
T 49500 47100 5 10 1 1 180 6 1
refdes=U1
T 49500 47300 5 10 1 1 180 6 1
value=LM311
T 49700 47600 5 8 1 1 180 6 1
footprint=DIP8
}
N 49100 47400 49500 47400 4
N 49500 47400 49500 47600 4
C 46600 49500 1 0 0 comparator_pwr.sym
{
T 46690 51500 5 8 0 0 0 0 1
symversion=1.0
T 47000 50400 5 10 1 1 0 1 1
refdes=U1
}
N 46900 50400 46900 50600 4
C 46800 49100 1 0 0 gnd-1.sym
N 46900 49400 46900 49500 4
C 53800 46800 1 0 1 connector8-1.sym
{
T 53700 50000 5 10 0 0 0 6 1
device=CONNECTOR_8
T 53900 49400 5 10 1 1 0 6 1
refdes=CONN1
T 53800 46800 5 10 0 0 0 0 1
footprint=HEADER8_1
T 53700 46500 5 10 1 1 0 0 1
value=J1
}
C 52000 46400 1 0 0 gnd-1.sym
N 52100 46700 52100 47900 4
C 51600 48600 1 0 0 5V-plus-1.sym
N 51200 47800 51200 49100 4
N 51200 47800 50200 47800 4
N 52100 48200 52100 48800 4
N 52100 48500 51800 48500 4
N 51800 48500 51800 48600 4
N 51200 49100 52100 49100 4
C 44800 44100 1 0 0 connector2-1.sym
{
T 45000 45100 5 10 0 0 0 0 1
device=CONNECTOR_2
T 44800 44900 5 10 1 1 0 0 1
refdes=CONN2
T 45100 43900 5 10 1 1 0 0 1
value=J2
T 44800 44100 5 10 0 0 0 0 1
footprint=HEADER2_1
}
N 46500 44300 47600 44300 4
N 47600 44300 47600 45700 4
