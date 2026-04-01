FROM ubuntu:24.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        clang-16 \
        clang-format-16 \
        clangd-16 \
        cmake \
        make \
        git \
        gdb \
        valgrind \
        vim \
        python3 \
        python3-pip \
        && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Create symlinks for clang tools (VS Code expects clangd without version number)
RUN ln -sf /usr/bin/clangd-16 /usr/bin/clangd && \
    ln -sf /usr/bin/clang-format-16 /usr/bin/clang-format && \
    ln -sf /usr/bin/clang++-16 /usr/bin/clang++ && \
    ln -sf /usr/bin/clang-16 /usr/bin/clang

# Set working directory
WORKDIR /workspace

# Default command
CMD ["/bin/bash"]