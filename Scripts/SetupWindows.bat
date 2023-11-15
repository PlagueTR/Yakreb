@echo off

pushd %~dp0\..\

echo Setting up Python virtual environment...
if not exist Scripts/Utility/Python/venv python -m venv Scripts/Utility/Python/venv
call Scripts/Utility/Python/venv/Scripts/activate.bat
python Scripts/Utility/Python/Setup.py

popd

PAUSE
