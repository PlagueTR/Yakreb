import subprocess

from SetupPython import PythonRequirements

PythonRequirements.Validate()

import Utilities

import colorama
from colorama import Back, Style

colorama.init()

from SetupPremake import PremakeRequirements

premakeInstalled = PremakeRequirements.Validate()

print("Updating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

print(f"{Style.BRIGHT}{Back.GREEN}Setup complete{Style.RESET_ALL}")