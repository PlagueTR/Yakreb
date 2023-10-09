import os
import subprocess

from SetupPython import PythonRequirements

PythonRequirements.Validate()

from SetupPremake import PremakeRequirements

os.chdir("./../")

premakeInstalled = PremakeRequirements.Validate()

print ("Updating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])
