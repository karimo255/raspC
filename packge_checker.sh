#!/bin/sh

for P; do
    dpkg -s "$P" >/dev/null 2>&1 && {
        echo "$P is installed."
    } || {
        echo "$P is not installed."
    }
done
