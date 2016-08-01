#!/bin/sh
rm imgHistos
./imgHistosBuild.sh 
./imgHistos $1
convert *.pdf histos.pdf
mv histos.pdf tmpdir/
rm *.pdf
