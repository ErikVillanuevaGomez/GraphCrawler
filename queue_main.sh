#!/bin/bash
#SBATCH --job-name=GraphCrawler
#SBATCH --partition=Centaurus
#SBATCH --time=00:10:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

cd $HOME/GraphCrawler

make clean
make

rm -f results.txt

echo "Running Tom Hanks (Depth 2)..." >> results.txt
./GraphCrawler "Tom_Hanks" 2 >> results.txt

echo "Running Tom Hanks (Depth 3)..." >> results.txt
./GraphCrawler "Tom_Hanks" 3 >> results.txt

echo "Running Kevin Bacon (Depth 2)..." >> results.txt
./GraphCrawler "Kevin_Bacon" 2 >> results.txt
