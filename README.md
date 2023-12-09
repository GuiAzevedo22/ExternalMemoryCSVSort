# External Sorting for CSV Files

## Overview

This is a group project focused on implementing external sorting for CSV files. The goal is to efficiently sort large CSV datasets that do not fit into the computer's main memory. External sorting is a technique that involves dividing the dataset into smaller chunks that can fit into memory, sorting those chunks, and then merging them to produce the final sorted output.

## Features

- **External Sorting**: Implementing external sorting algorithms to handle large CSV files.
- **CSV and Binary File Handling**: Reading and writing CSV files efficiently.
- **Sorting method**: Our choice for external sorting method was disk merge sort and for internal sort we used quick sort.

## How to run

```
  g++ -Wall ./(file_name).cpp -o exec.exe
./exec
```
## Contributors

[Frederico Maia](https://github.com/fredmaia)<br>
[Gabriel Ferreira](https://github.com/Ferreira327)<br>
