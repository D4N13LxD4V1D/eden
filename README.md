<!-- # [![Eden](assets/branding/logo.svg)](https://)

[![CI](https://github.com/D4N13LxD4V1D/eden/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/D4N13LxD4V1D/eden/actions) -->

## What is Eden?

Eden is an Entity-Component-System (ECS) game engine written entirely from scratch without relying on any external libraries. It is designed to be lightweight, modular, and efficient, providing a solid foundation for building games and simulations.

## Features

- **Entity-Component-System Architecture**: Leverages the ECS pattern to provide a flexible and efficient way to manage game objects and their behaviors.
- **Modular Design**: Each part of the engine is designed as a module, making it easy to extend and customize.
- **Cross-Platform**: Supports multiple platforms, including macOS with Metal for rendering.

## Getting Started

### Prerequisites

- C++23 compatible compiler
- CMake 3.31.3 or higher
- Ninja build system (optional but recommended)

### Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/D4N13LxD4V1D/eden.git
    cd eden
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Configure the project using CMake:
    ```sh
    cmake .. -G Ninja
    ```

4. Build the project:
    ```sh
    ninja
    ```