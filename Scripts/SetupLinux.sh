#!/bin/bash

pushd "$(dirname "$0")/../" > /dev/null

python Scripts/Utility/Python/Setup.py

popd > /dev/null

read -n1 -r -p "Press any key to continue..."
echo ""
