# externalsort

    main.cpp
    
    exsort.cpp exsort.h
external sort functions

    randomstrings.cpp randomstrings.h
functions dedicated to a generation of random strings

## ./externalSort

    -h --help
Shows this.

    -v --validate
Checks whatever the file is sorted line by line.

    -g --generate NLENGTH NLINES
Generates a random text file with NLINES lines, each line has a random length with a maximum of NLENGTH.
(!) writes every new line to output, slower

    -bg --blockgenerate S_LEN N_STRS
Generates a text file with N_STRS lines, each line has a length of S_LEN.

    -sg --spaghettigenerate S_LEN N_STRS
Generates a text file with N_STRS lines, each line has a random length with a maximum S_LEN.

    -sb --boundedgenerate S_LEN N_STRS MEMORY_BOUND
Generates a text file with N_STRS lines, each line has a random length with a maximum S_LEN.
saves strings to a buffer of the size MEMORY_BOUND (default value 19MB)

    -b --bitgenerate S_LEN LIMIT
Generates with size greater than LIMIT, random strings with a maximum size S_LEN.
(!) writes every new line to output, slower

    -s --sort INPUT OUTPUT SIZE
Sorts INPUT file using an external search by splitting it to chunks of the SIZE, writes a result to output.

## utils

    bitrun.sh S_LEN N_STRS
    
Bash script that generates strings via blockgenerate, sorts them by the means of the program, then sorts by the means of standard sort, checks both results with wc and diff.

