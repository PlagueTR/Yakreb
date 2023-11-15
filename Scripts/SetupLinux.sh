#!/bin/bash

pushd "$(dirname "$0")/../" > /dev/null

echo "Setting up Python virtual environment..."
[ ! -d Scripts/Utility/Python/venv ] && python -m venv Scripts/Utility/Python/venv
source Scripts/Utility/Python/venv/bin/activate
python Scripts/Utility/Python/Setup.py

popd > /dev/null

read -n1 -r -p "Press any key to continue..."
echo ""
