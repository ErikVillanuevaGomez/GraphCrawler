# Graph Crawler in C++





# Build instructions

Run the following commands in the project directory:



    make clean

    make

    

This creates an executable named GraphCrawler.



# Usage

Next run the following command with the desired simulation parameters:



    ./GraphCrawler "<start_node>" <depth>


<start_node> The name of the starting actor or movie (must be in quotes)

<depth> The integer depth to traverse from the start node


For example, to run a search starting from Tom Hanks with a depth of 2:

    ./GraphCrawler "Tom Hanks" 2




# Clean

To remove the compiled executable run the following command:



    make clean



# BenchMark

When Benchmarking on Centaurus:



    cd GraphCrawler

    chmod +x queue_main.sh

    sbatch queue_main.sh
    
If you recieve an error on Centaurus like rapidjson/document.h: No such file or directory, run the following commands in the project directory:

    rm -rf rapidjson
    
    git clone https://github.com/Tencent/rapidjson.git

After cloning, sbatch again.
    

This creates the file results.txt, which contains the output and runtimes for the benchmark cases defined in the queue_main.sh script.

