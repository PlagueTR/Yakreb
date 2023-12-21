import sys
import os
import colorama
from colorama import Back, Style
from pathlib import Path

import Utilities


class PremakeRequirements:
    premakeVersion = "5.0.0-beta2"
    premakeZipUrl = "https://github.com/premake/premake-core/releases/download/v{0:s}/premake-{0:s}-windows.zip".format(premakeVersion)
    premakeTarUrl = "https://github.com/premake/premake-core/releases/download/v{0:s}/premake-{0:s}-linux.tar.gz".format(premakeVersion)
    premakeLicenseUrl = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"
    premakeDirectory = "./vendor/premake/bin"
    colorama.init()

    @classmethod
    def Validate(cls):
        if not cls.CheckPremakeInstallation():
            print(f"{Style.BRIGHT}{Back.RED}Premake is not installed.{Style.RESET_ALL}")
            return False
        print(f"{Style.BRIGHT}{Back.GREEN}Correct Premake located at {os.path.abspath(cls.premakeDirectory)}{Style.RESET_ALL}")
        return True

    @classmethod
    def CheckPremakeInstallation(cls):
        premakeExeWin = Path("{0:s}/premake5.exe".format(cls.premakeDirectory))
        premakeExeLin = Path("{0:s}/premake5".format(cls.premakeDirectory))
        if (not premakeExeWin.exists()) and (not premakeExeLin.exists()):
            return cls.InstallPremake()
        return True

    @classmethod
    def InstallPremake(cls):
        while True:
            print("Premake not found. Would you like to download Premake?")
            response = Utilities.YesOrNo()
            if response:
                premakePathWin = "{0:s}/premake-{1:s}-windows.zip".format(cls.premakeDirectory, cls.premakeVersion)
                premakePathLin = "{0:s}/premake-{1:s}-linux.tar.gz".format(cls.premakeDirectory, cls.premakeVersion)
                if sys.platform == "win32":
                    print("Downloading {0:s} to {1:s}".format(cls.premakeZipUrl, premakePathWin))
                    Utilities.DownloadFile(cls.premakeZipUrl, premakePathWin)
                    print("Extracting")
                    Utilities.UnzipFile(premakePathWin, files=["premake5.exe"], deleteZipFile=True)
                elif sys.platform == "linux":
                    print("Downloading {0:s} to {1:s}".format(cls.premakeTarUrl, premakePathLin))
                    Utilities.DownloadFile(cls.premakeTarUrl, premakePathLin)
                    print("Extracting")
                    Utilities.UntarFile(premakePathLin, files=["premake5"] ,deleteTarFile=True)
                premakeLicensePath = "{0:s}/LICENSE.txt".format(cls.premakeDirectory)
                print("Downloading {0:s} to {1:s}".format(cls.premakeLicenseUrl, premakeLicensePath))
                Utilities.DownloadFile(cls.premakeLicenseUrl, premakeLicensePath)
                return True