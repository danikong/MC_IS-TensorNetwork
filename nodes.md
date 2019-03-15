# Fragen 20.09.2018

- [x] importance sampling mit welchen Tensor
- [x] Gewichtungsfaktor auch bei anderen tensoren aufmultiplizieren
- [x] berechneter Wert: 0.00672938  + i0.0255581 ?

# Erwartungswerte

## test1

Calculated Tsum = (1167.14,9.15934e-16)
dt = 0.0012

{4,4,4,4}
V: E = (1167.14,0)
dt = 0.00014

{8,8}
K: E = (1167.14,0)
dt = 6.2e-05

C: E = (1167.14,-9.6971e-16)
dt = 0.000691


<E_real/N> = 0.07123657226

## test2

Calculated Tsum = (1586.94,7.93809e-15)
dt = 0.001114

{4,4,4,4}
V: E = (1586.94,0)
dt = 0.000103

{8,8}
K: E = (1586.94,0)
dt = 6.2e-05

C: E = (1586.94,1.18117e-14)
dt = 0.000671

<E_real/N> = 0.09685913085

## test3

Calculated Tsum = (1147.66,2.70201e-14)
dt = 0.00113

{4,4,4,4}
V: E = (1147.66,0)
dt = 0.000128

{8,8}
K: E = (1147.66,0)
dt = 6.7e-05

C: E = (1147.66,-3.3864e-14)
dt = 0.000713


<E_real/N> = 0.07004760742

## test4

Calculated Tsum = (1.46242e+07,2.80124e-10)
dt = 0.001067

{4,4,4,4}
V: E = (1.46242e+07,0)
dt = 0.000153

{8,8}
K: E = (1.46242e+07,0)
dt = 6.1e-05

C: E = (1.46242e+07,-1.70985e-10)
dt = 0.000661


<E_real/N> = 892.590332031

## FTODDUMP_MC small

{32,32,32,32}
1
V: E_real = 0.0586645
V: E_img = 0
dt = 100.065

{534,534}
2
K: E_real = 0.0586645 --> 1.9619726e-13
K: E_img = 0
dt = 78.6463

## FTODDUMP_MC large

dt = 9.307 #readin

{64,32,64,32}
V: E = (1.93167,0) #False!!!!!!!
dt = 490.824

{534,534}
K: E = (1.04764,0) --> 8.7593051e-13
dt = 163.985


## test_is

Calculated Tsum = (256293,1.24345e-12)
dt = 0.001147


{4,4,4,4}
V: E = (256293,0)
dt = 0.000135

{8,8}
K: E = (256293,0)
dt = 6.1e-05

C: E = (256293,1.24345e-12)
dt = 0.000728


<E_real/N> = 15.6428833008


#TODO

- [x] uniform sampling konvergiert immer um berechneten Erwartungswert
- [x] Importance sampling überprüfen da falsche ergenbisse geliefert werden
- [x] `weight` überprüfen ob richtiges genommen wird
- [x] Fehler suchen warum bei `FTODDUMP_MC` "random" segmentation fault Errors auftreten


# Fragen 18.10

- [x] zur Überprüfung Tensor erzeugen und Verteilung der Inversion Methode ploten
- [x] verwendeten Random Number Generator?
- [x] Erwartungswerte (da komplex?)
\[ {\overline {X}}={\frac {1}{n}}\sum _{i=1}^{n}X_{i} \]
- [x] Varianz (da komplex?)
\[ V_{n}^{*}(X)={\frac {1}{n-1}}\sum _{i=1}^{n}(X_{i}-{\overline {X}})^{2} \]
- [x] "random" segmentation fault errors --> beim aufruf von `Tnet.sampleTNet(...)`

# Fragen < nextTime >
- [x] `weight` bei UD sampling bzw nur bei importance sampling berücksichtigt
- [x] convergenz von `FTODDUMP_MC` ist nicht gleich dem errechneten jedoch alle alle anderen schon



# Besprechung 27.11.
- [ ] recenter
- [ ] consistency check
- [ ] thread
      openMP
      --> mpi  - compiler: mpicxx


# Besprechung 21.02.
no uniform
Direct exchange (2-3 sampling methodes)
triples

computational physics thijssen
modern quantum chemistry attila szabo and neil ostlund


asymtote vectorgraphic
grüneis und hummel tensor rank decomposition ... paper gamma tensor

curse of Dimension
