#!/bin/bash

cd cmake-build-debug/BTS && konsole -e ./BTS &
cd cmake-build-debug/UE && konsole -e ./UE phone=1 &
cd cmake-build-debug/UE && konsole -e ./UE phone=2 &