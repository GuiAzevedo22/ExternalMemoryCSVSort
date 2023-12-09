# External Sorting for CSV Files

## Overview

This a group project focused on implementing external sorting for CSV files. The goal is to efficiently sort large CSV datasets that do not fit into the computer's main memory. External sorting is a technique that involves dividing the dataset into smaller chunks that can fit into memory, sorting those chunks, and then merging them to produce the final sorted output.

## Features

- **External Sorting**: Implementing external sorting algorithms to handle large CSV files.
- **CSV File Handling**: Reading and writing CSV files efficiently.
- **Configurability**: The project provides flexibility in configuring parameters such as chunk size, sorting algorithm, and other relevant options.
- **Performance Optimization**: Optimizing the sorting process for performance gains, considering factors like I/O operations and memory usage.
- **User Interface (Optional)**: Optionally, a simple command-line interface or graphical user interface for user interaction.
- **Ordenation method**: Our choice for external ordenation method was disk merge sort and for internal sort we used quick sort.

## How to run

```
  g++ -Wall ./(file_name).cpp -o exec.exe
./exec
```
## Contributors

[Frederico Maia](https://github.com/fredmaia)<br>
[Gabriel Ferreira](https://github.com/Ferreira327)<br>
