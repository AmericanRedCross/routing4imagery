#!/bin/bash

echo "Input filename:"
read INFILENAME
echo "Output filename:"
read OUTFILENAME
echo "Creating route for $INFILENAME"

# cargo install osm4routing
git clone https://github.com/Tristramg/osm4routing2.git
git clone https://github.com/rkistner/chinese-postman.git

mv $INFILENAME osm4routing2
cd osm4routing2/

cargo build
cargo run $INFILENAME

mv nodes.csv ../
mv edges.csv ../
cd ..
g++ -O3 -m64 -Wall postmanextract.cpp -o postmanextract
./postmanextract nodes.csv edges.csv

python3 -m venv env
source env/bin/activate
pip install networkx
pip install matplotlib
pip install pandas
pip install numpy

python3 chinese-postman/postman.py postman_input.csv > $OUTFILENAME

echo "Processes finished. Path output file: $OUTFILENAME"