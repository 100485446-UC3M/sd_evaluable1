#!/bin/bash

# Script to start 10 clients

# Define directories and executables based on the Makefile
BIN_DIR="bin"
CLIENT_EXEC="app-cliente"
CLIENT_PATH="$BIN_DIR/$CLIENT_EXEC"

# Check if the executables exist, if not build them
if [ ! -f "$CLIENT_PATH" ]; then
    echo "Building executables..."
    make clean
    make all
fi

if [ ! -f "$CLIENT_PATH" ]; then a server and 1
    echo "Error: Client executable not found at $CLIENT_PATH"
    exit 1
fi

# Start 10 clients
echo "Starting 10 clients..."
CLIENT_PIDS=()

for i in {1..10}; do
    echo "Starting client $i"
    $CLIENT_PATH &
    CLIENT_PIDS+=($!)
done

# Wait for user input to terminate
echo "Press Enter to terminate all processes..."
read

# Kill clients
echo "Terminating clients..."
for pid in "${CLIENT_PIDS[@]}"; do
    kill $pid 2>/dev/null
done

echo "All clients terminated."