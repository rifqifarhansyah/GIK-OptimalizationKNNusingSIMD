# **Garuda Ilmu Komputer** - Weekly Task
<h2 align="center">
  K-Nearest Neighbor Optimalization using SIMD<br/>
</h2>
<hr>

## Table of Contents
1. [General Info](#general-information)
2. [Creator Info](#creator-information)
3. [Features](#features)
4. [Technologies Used](#technologies-used)
5. [Setup](#setup)
6. [Usage](#usage)
7. [Screenshots](#screenshots)
8. [Structure](#structure)
9. [Project Status](#project-status)
10. [Room for Improvement](#room-for-improvement)
11. [Acknowledgements](#acknowledgements)
12. [Contact](#contact)

<a name="general-information"></a>

## General Information
A simple program to extend K-Nearest Neighbor algorithm that have been made in the first week. The program will randomly generate 1000 data points with `n` dimensional data. The program will then ask user input for `coordinate value` that want to be assigned as pivot point. After that, the program will ask user input for `K value`. The program will then calculate the `distance` between the pivot point and all the data points (The additional feature from the last week is the optimalization using SIMD concept, it can be happen by calculate the set of dataset concurrently). The program will then `sort the data points` based on the distance from the pivot point. The program will then show the K nearest data points to the pivot point. This program is made for GIK research program - ML Topics at Week02-April.

<a name="creator-information"></a>

## Creator Information

| Nama                        | NIM      | E-Mail                      |
| --------------------------- | -------- | --------------------------- |
| Mohammad Rifqi Farhansyah   | 13521166 | 13521166@std.stei.itb.ac.id |

<a name="features"></a>

## Features
- Generate `1000 data points` with 2 features (x and y)
- Ask user input for `n` value (dimension of the data points)
- Ask user input for `coordinate` value that want to be assigned as pivot point
- Ask user input for `K` value
- `Calculate the distance between` the pivot point and all the data points
- `Sort the data points` based on the distance from the pivot point
- Show the `K nearest data points` to the pivot point
- `Save the K nearest data points` to the text file
- `Optimalization using SIMD` concept
- Print the `execution time` of the program

<a name="technologies-used"></a>

## Technologies Used
- MingGw-W64 version 8.1.0

> Note: The version of the libraries above is the version that we used in this project. You can use the latest version of the libraries.

<a name="setup"></a>

## Setup
1. Download the MingW-W64 from [here](https://sourceforge.net/projects/mingw-w64/files/).
2. Install the MingW-W64.

<a name="usage"></a>

## Usage
1. Open the terminal in the project directory.
2. `cd output` and then `k_nearest_neighbor_SIMD.exe` to run the program.
3. Input the n value (dimension of the data points).
3. Input the coordinate value that want to be assigned as pivot point.
4. Input the K value.
5. The program will then calculate the distance between the pivot point and all the data points.
6. Program will sort the data points based on the distance from the pivot point.
7. KNN Simple Program will output the K nearest data points to the pivot point.
8. Program will show the execution time of the program.

<a name="screenshots"></a>

## Screenshots
<p>
  <img src="/image/SS1.png/">
  <p>Figure 1. Input</p>
  <nl>
  <img src="/image/SS2.png/">
  <p>Figure 2. Result</p>
  <nl>
  <img src="/image/SS3.png/">
  <p>Figure 3. Time Execution</p>
  <nl>
</p>

<a name="structure"></a>

## Structure
```bash
│   k_nearest_neighbour_SIMD.cpp
│   README.md
│
├───image
│       SS1.png
│       SS2.png
│       SS3.png
│
└───output
        k_nearest_neighbour_SIMD.exe
        near_points_file.txt
```

<a name="project-status">

## Project Status
Project is: _complete_

<a name="room-for-improvement">

## Room for Improvement
Room for Improvement:
- Add more features

<a name="acknowledgements">

## Acknowledgements
- Thanks To Allah SWT

<a name="contact"></a>

## Contact
<h4 align="center">
  Contact Me : mrifki193@gmail.com<br/>
  2023
</h4>
<hr>
