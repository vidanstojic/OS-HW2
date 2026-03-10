# xv6 File System Extensions

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![xv6](https://img.shields.io/badge/OS-xv6-000000?style=for-the-badge&logo=linux&logoColor=white)
![FileSystem](https://img.shields.io/badge/FileSystem-Symbolic_Links-A8B9CC?style=for-the-badge&logo=files&logoColor=white)
![Status](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge)

This repository contains advanced file system extensions for the xv6 operating system. The project focuses on the implementation of symbolic links and comprehensive disk usage analysis tools, enhancing the system's ability to handle complex file structures and storage monitoring.

## Overview

The implementation introduces a redirection mechanism through symbolic links and a recursive utility for calculating disk space consumption. These features are integrated at the kernel level to ensure atomic operations and consistent file system behavior across both system calls and user-space utilities.

## Technical Implementation

* **Symbolic Link Integration**: Added a new inode type to represent symbolic links, allowing paths to point to other files or directories.
* **Kernel Path Resolution**: Modified the file opening logic to handle recursive link traversal while maintaining system performance.
* **Storage Tracking**: Updated core data structures to include block-level information, enabling accurate measurement of physical disk usage.
* **Safety Mechanisms**: Implemented specialized flags for file operations to control link dereferencing and prevent infinite loops in path resolution.

## Features

### 1. System-Level Enhancements
* **System Call Layer**: A dedicated system call for creating symbolic links between different paths in the file system.
* **Enhanced Stat Structure**: The internal file status structure now includes physical block counts, providing a more granular view of resource allocation.
* **Link Control**: Support for opening files without following symbolic links, essential for diagnostic and management tools.

### 2. User Utilities
* **Symbolic Link Creator**: A command-line tool for generating links within the file system hierarchy.
* **Link Diagnostic Tool**: A utility for inspecting existing symbolic links, providing details about their targets and validity.
* **Disk Usage Analyzer**: A recursive tool that traverses directory structures to calculate and display the total storage footprint of files and folders.

### 3. Visual and Operational Updates
* **Directory Listing**: The standard list command has been updated to display block usage and correctly identify symbolic links.
* **Recursion Support**: Deep directory traversal for disk space calculation, handling varied file types and link structures.
