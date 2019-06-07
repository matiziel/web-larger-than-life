#!/bin/bash

(cd ./larger_than_life/models/src && make)
python3.6 launch.py
