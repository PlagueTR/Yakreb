import sys
import os
import platform
from pathlib import Path

import Utilities

class PremakeRequirements:
    premakeVersion = "5.0.0-beta2"
    premakeZipUrl = "https://github.com/premake/premake-core/releases/download/v{0:s}/premake-{0:s}-windows.zip".format(premakeVersion)
    premakeTarUrl = "https://github.com/premake/premake-core/releases/download/v{0:s}/premake-{0:s}-linux.tar.gz".format(premakeVersion)
    premakeLicenseUrl = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"
    premakeDirectory = "./vendor/premake/bin"

    @classmethod
    def Validate(cls):
        if (not cls.CheckPremakeInstallation()):
            print("Premake is not installed.")
            return False
        print("Correct Premake located at {0:s}".format(os.path.abspath(cls.premakeDirectory)))
        return True

    @classmethod
    def CheckPremakeInstallation(cls):
        premakeExeWin = Path("{0:s}/premake5.exe".format(cls.premakeDirectory))
        premakeExeLin = Path("{0:s}/premake5".format(cls.premakeDirectory))
        if ((not premakeExeWin.exists()) or (not premakeExeLin.exists())):
            return cls.InstallPremake()
        return True

    @classmethod
    def InstallPremake(cls):
        while True:
            reply = str(input("Premake not found. Would you like to download Premake? [Y/N]: "))
            if ((reply == 'n') or (reply == 'N')):
                return False
            elif ((reply == 'y') or (reply == 'Y')):
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
                    Utilities.UntarFile(premakePathLin, compression="gz", files=["premake5"] ,deleteTarFile=True)
                premakeLicensePath = "{0:s}/LICENSE.txt".format(cls.premakeDirectory)
                print("Downloading {0:s} to {1:s}".format(cls.premakeLicenseUrl, premakeLicensePath))
                Utilities.DownloadFile(cls.premakeLicenseUrl, premakeLicensePath)
                return True