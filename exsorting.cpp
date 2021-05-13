//
// Created by vadim on 11.05.2021.
//

#include "exsorting.h"

// The entire meaning of the procedure follows this:
// We can't put the file into the memory in the entirety
// hence we read the file line-by-line until we reach the memory limit
// when we reach memory limit we sort this chunk and write it on the disk
// then proceed in the same manner until the file ends
// when the file ends we use merge sort to combine the existing chunks
// into one file again

size_t process_input(const std::string &input_name, const std::string &stamp, size_t memoryLimit) {

    std::ifstream input_file;

    input_file.open(input_name.c_str());

    size_t memory_used = 0;
    unsigned int numberChunks = 0;

    std::ofstream output;
    std::vector<std::string> data;

    data.clear();

    // reads a file line by line, and checks whatever the memory limit is breached
    // if the limit is breached, writes into a file
    for (std::string line; std::getline(input_file, line);) {

        if (memory_used + line.size() < memoryLimit) {

            memory_used = memory_used + line.size() + 1;
            data.push_back(line);

        } else {
            write_chunk(data, numberChunks, output, stamp);
            data.clear();

            memory_used = line.size();
            data.push_back(line);

        }
    }

    // writing leftovers for the last chunk
    if (!data.empty()) {
        write_chunk(data, numberChunks, output, stamp);
    }

    input_file.close();

    return numberChunks;
}

void write_chunk(std::vector<std::string> &data, unsigned int &numberChunks,
                 std::ofstream &output, const std::string &stamp) {

    sort(data.begin(), data.end());

    numberChunks++;

    std::stringstream basicStringStream;
    basicStringStream << "chunk_" << numberChunks << "_" << stamp << ".txt";

    output.open(basicStringStream.str());

    size_t data_size = data.size();

    for (int i = 0; i < data_size - 1; i++) {
        output << data[i];
        output << std::endl;
    }

    if (data_size > 0) {
        output << data[data_size - 1];
    }

    output.close();
}

// comparator for heap structure in the merge sort of different chunks
class Compare {
public:
    bool operator()(const std::pair<std::string, size_t> &pair1,
                    const std::pair<std::string, size_t> &pair2) {
        return pair1.first > pair2.first;
    }
};

// merges different chunks from files through the merge sort
void merge(size_t numberChunks, const std::string &stamp, const std::string &output_name) {

    // a heap that is needed to implement the merge sort
    std::priority_queue<
            std::pair<std::string, size_t>,
            std::vector<std::pair<std::string, size_t> >,
            Compare> minHeap;

    auto *chunks = new std::ifstream[numberChunks];

    // reads the chunks in the initial pass
    // fills the array of pointers to streams related to every chunk
    // fills the minimum heap with first lines from the chunks and the chunk number
    for (int i = 0; i < numberChunks; i++) {

        std::string topString;
        std::string currentFile = "chunk_" + std::to_string(i + 1) + "_" + stamp + ".txt";

        chunks[i].open(currentFile.c_str());

        std::getline(chunks[i], topString);

        minHeap.push(std::pair<std::string, size_t>(topString, i));

    }

    std::ofstream output_file(output_name.c_str());

    // while the heap is not empty proceeds to pop the smallest element
    // prints it into an output file and puts the next element
    // from the same file into the heap
    while (!minHeap.empty()) {

        std::pair<std::string, size_t> minE = minHeap.top();
        minHeap.pop();
        output_file << minE.first;
        output_file << std::endl;

        std::string nextValue;
        flush(output_file);

        if (!chunks[minE.second].eof()) {
            std::getline(chunks[minE.second], nextValue);
            minHeap.push(std::pair<std::string, size_t>(nextValue, minE.second));
        }
    }

    for (int i = 0; i < numberChunks; i++) {
        chunks[i].close();
    }
    output_file.close();

    delete[] chunks;

}

// deletes temporary chunks needed to safe data on the disk
void clear_chunks(size_t numberChunks, const std::string &stamp) {
    for (int i = 0; i < numberChunks; i++) {
        std::stringstream ss;
        ss << "chunk_" << (i + 1) << "_" << stamp << ".txt";
        remove(ss.str().c_str());
    }
}
