#!/usr/bin/env bash

cmake -B build
cmake --build build

sudo mv build/plusy /usr/local/bin/

echo "installed successfully!"
