#!/bin/sh

set -e

if [ ! -f "./btwfetch" ]; then
    echo "error: btwfetch binary not found"
    exit 1
fi

sudo mkdir -p /usr/local/bin
sudo mkdir -p ~/.config/btwfetch

sudo cp ./btwfetch /usr/local/bin/btwfetch
sudo chmod +x /usr/local/bin/btwfetch

cp ./config/config.conf ~/.config/btwfetch/config.conf

echo "btwfetch installed successfully"
