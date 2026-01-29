# Development environment for C++ console application
FROM ubuntu:22.04

# Install C++ development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    gdb \
    make \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source files
COPY . /app/

# Default to bash shell for development
CMD ["/bin/bash"]