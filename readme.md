# fun-with-threads

This a small project used to show how threads can be used to improve performance 
of programs which need to do a lot of computation.s It was made for a talk about
Node.js event loop during the first metup of JsBenin.

The purpose af the programs is to genarate stats about blood group for some West
Africa countries.

# Requirements

This code was written and tested on Ubuntu 20.04.
The only requirement is the `pthread` lib which should be available by default on the system.

# Data Generation

The data folder contains a Python script named `gen_data.py`. Run it to generate the data
needed by the programs.

```sh
cd ./data
python3 gen_data.py
```

# Compilation

After data generation, cd back in the root folder and compile the programs.

```sh
cd ..
g++ -o stats -std=c++17 stats.cpp -lpthread
g++ -o tstats -std=c++17 stats-with-threads.cpp -lpthread
```

You can then issue the following commands to run and measure time.

```sh
time ./stats
time ./tstats
```
# License

Creative Commons Attribution Share Alike 4.0
