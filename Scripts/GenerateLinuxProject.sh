#!/bin/bash

pushd "$(dirname "$0")/../" > /dev/null

./vendor/premake/bin/premake5 codeblocks

popd > /dev/null

read -n1 -r -p "Press any key to continue..."
echo ""