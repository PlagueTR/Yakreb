import sys
import subprocess
import importlib.util as importlib_util

class PythonRequirements:
    packages = ["requests"]

    @classmethod
    def Validate(cls):
        if not cls.__ValidatePython():
            return

        for package in cls.packages:
            if not cls.__ValidatePackage(package):
                return

    @classmethod
    def __ValidatePython(cls, versionMajor = 3, versionMinor = 3):
        if sys.version is not None:
            print("Python version {0:d}.{1:d}.{2:d} detected.".format(sys.version_info.major, sys.version_info.minor, sys.version_info.micro))
            if ((sys.version_info.major < versionMajor) or ((sys.version_info.major == versionMajor) and (sys.version_info.minor < versionMinor))):
                print("Python version too low, expected version {0:d}.{1:d} or higher.".format(versionMajor, versionMinor))
                return False
            return True

    @classmethod
    def __ValidatePackage(cls, package):
        if importlib_util.find_spec(package) is None:
            return cls.__InstallPackage(package)
        return True

    @classmethod
    def __InstallPackage(cls, package):
        while True:
            reply = str(input("Python package '{0:s}' is required for the setup script, would you like to install {0:s}? [Y/N]".format(package)))
            if ((reply == 'n') or (reply == 'N')):
                return False
            elif ((reply == 'y') or (reply == 'Y')):
                print("Installing {0:s}...".format(package))
                subprocess.check_call([sys.executable, "-m", "pip", "install", package])
                return cls.__ValidatePackage(package)

if __name__ == "__main__":
    PythonRequirements.Validate()
