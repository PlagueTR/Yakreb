import sys
import os

import requests
import time
import urllib

from zipfile import ZipFile
from tarfile import TarFile

import colorama
from colorama import Back, Style

colorama.init()


def YesOrNo():
    while True:
        reply = str(input("[Y/N]: ")).lower().strip()
        if reply[:1] == 'y':
            return True
        if reply[:1] == 'n':
            return False


def DownloadFile(url, filepath):
    filepath = os.path.abspath(filepath)
    os.makedirs(os.path.dirname(filepath), exist_ok=True)
    if (type(url) is list):
        for url_option in url:
            print("Trying to download {0:s}".format(url_option))
            try:
                DownloadFile(url_option, filepath)
                return
            except urllib.error.URLError as e:
                print(f"{Style.BRIGHT}{Back.YELLOW}URL Error encountered: {e.reason}. Proceeding with backup...{Style.RESET_ALL}")
                os.remove(filepath)
                pass
            except urllib.error.HTTPError as e:
                print(f"{Style.BRIGHT}{Back.YELLOW}HTTP Error encountered: {e.code}. Proceeding with backup...{Style.RESET_ALL}")
                os.remove(filepath)
                pass
            except:
                print(f"{Style.BRIGHT}{Back.YELLOW}Unknown error. Proceeding with backup...{Style.RESET_ALL}")
                os.remove(filepath)
                pass
        raise ValueError(f"{Style.BRIGHT}{Back.RED}Failed to download {filepath}{Style.RESET_ALL}")
    if (not(type(url) is str)):
        raise TypeError("Argument 'url' must be of type list or string")
    with open(filepath, 'wb') as file:
        headers = {'User-Agent': "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36"}
        response = requests.get(url, headers=headers, stream=True)
        total = response.headers.get('content-length')
        if total is None:
            file.write(response.content)
        else:
            downloaded = 0
            total = int(total)
            startTime = time.time()
            for data in response.iter_content(chunk_size=max(int(total / 1000), 1024 * 1024)):
                downloaded += len(data)
                file.write(data)
                try:
                    done = int(50 * downloaded / total) if downloaded < total else 50
                    percentage = (downloaded / total) * 100 if downloaded < total else 100
                except ZeroDivisionError:
                    done = 50
                    percentage = 100
                elapsedTime = time.time() - startTime
                try:
                    avgKBPerSecond = (downloaded / 1024) / elapsedTime
                except ZeroDivisionError:
                    avgKBPerSecond = 0.0
                avgSpeedString = "{0:.2f} KB/s".format(avgKBPerSecond)
                if (avgKBPerSecond > 1024):
                    avgMBPerSecond = avgKBPerSecond / 1024
                    avgSpeedString = '{0:.2f} MB/s'.format(avgMBPerSecond)
                sys.stdout.write('\r[{}{}] {:.2f}% ({})     '.format('█' * done, '.' * (50 - done), percentage, avgSpeedString))
                sys.stdout.flush()
    sys.stdout.write('\n')


def UnzipFile(filepath, files=None, deleteZipFile=True):
    zipFilePath = os.path.abspath(filepath)
    zipFileLocation = os.path.dirname(zipFilePath)
    zipFileContent = dict()
    with ZipFile(zipFilePath, 'r') as zipFileFolder:
        for name in zipFileFolder.namelist():
            zipFileContent[name] = zipFileFolder.getinfo(name).file_size
        zipFileContentSize = sum(zipFileContent.values())
        extractedContentSize = 0
        startTime = time.time()
        if (files is None):
            for zippedFileName, zippedFileSize in zipFileContent.items():
                UnzippedFilePath = os.path.abspath("{0:s}/{1:s}".format(zipFileLocation, zippedFileName))
                os.makedirs(os.path.dirname(UnzippedFilePath), exist_ok=True)
                if (os.path.isfile(UnzippedFilePath)):
                    zipFileContentSize -= zippedFileSize
                else:
                    zipFileFolder.extract(zippedFileName, path=zipFileLocation, pwd=None)
                    extractedContentSize += zippedFileSize
                try:
                    done = int(50*extractedContentSize/zipFileContentSize)
                    percentage = (extractedContentSize/zipFileContentSize) * 100
                except ZeroDivisionError:
                    done = 50
                    percentage = 100
                elapsedTime = time.time() - startTime
                try:
                    avgKBPerSecond = (extractedContentSize / 1024) / elapsedTime
                except ZeroDivisionError:
                    avgKBPerSecond = 0.0
                avgSpeedString = "{0:.2f} KB/s".format(avgKBPerSecond)
                if (avgKBPerSecond > 1024):
                    avgMBPerSecond = avgKBPerSecond / 1024
                    avgSpeedString = "{0:.2f} MB/s".format(avgMBPerSecond)
                sys.stdout.write('\r[{}{}] {:.2f}% ({})     '.format('█' * done, '.' * (50 - done), percentage, avgSpeedString))
                sys.stdout.flush()
            sys.stdout.write('\n')
        elif (type(files) is list):
            for file in files:
                if (not(type(file) is str)):
                    raise TypeError("Argument 'files' must be a list containing only str elements")
            print("File list found for extraction. Extracting only specified files.")
            filenum = 0
            totalFiles = len(files)
            for file in files:
                UnzippedFilePath = os.path.abspath("{0:s}/{1:s}".format(zipFileLocation, file))
                os.makedirs(os.path.dirname(UnzippedFilePath), exist_ok=True)
                zipFileFolder.extract(file, path=zipFileLocation, pwd=None)
                filenum+=1
                sys.stdout.write('\r{}/{} files extracted     '.format(filenum, totalFiles))
                sys.stdout.flush()
            sys.stdout.write('\n')
        else:
            raise TypeError("Argument 'files' must be a list containing only str elements")
    if deleteZipFile:
        os.remove(zipFilePath)


def UntarFile(filepath, files=None, deleteTarFile=True):
    tarFilePath = os.path.abspath(filepath)
    tarFileLocation = os.path.dirname(tarFilePath)
    tarFileContent = dict()
    with TarFile.open(tarFilePath, 'r') as tarFileFolder:
        for name in tarFileFolder.getnames():
            tarFileContent[name] = tarFileFolder.getmember(name).size
        tarFileContentSize = sum(tarFileContent.values())
        extractedContentSize = 0
        startTime = time.time()
        if (files is None):
            for tarredFileName, tarredFileSize in tarFileContent.items():
                UntarredFilePath = os.path.abspath("{0:s}/{1:s}".format(tarFileLocation, tarredFileName))
                os.makedirs(os.path.dirname(UntarredFilePath), exist_ok=True)
                if (os.path.isfile(UntarredFilePath)):
                    tarFileContentSize -= tarredFileSize
                else:
                    tarFileFolder.extract(tarredFileName, path=tarFileLocation, set_attrs=True)
                    extractedContentSize += tarredFileSize
                try:
                    done = int(50*extractedContentSize/tarFileContentSize)
                    percentage = (extractedContentSize/tarFileContentSize) * 100
                except ZeroDivisionError:
                    done = 50
                    percentage = 100
                elapsedTime = time.time() - startTime
                try:
                    avgKBPerSecond = (extractedContentSize / 1024) / elapsedTime
                except ZeroDivisionError:
                    avgKBPerSecond = 0.0
                avgSpeedString = "{0:.2f} KB/s".format(avgKBPerSecond)
                if (avgKBPerSecond > 1024):
                    avgMBPerSecond = avgKBPerSecond / 1024
                    avgSpeedString = "{0:.2f} MB/s".format(avgMBPerSecond)
                sys.stdout.write('\r[{}{}] {:.2f}% ({})     '.format('█' * done, '.' * (50 - done), percentage, avgSpeedString))
                sys.stdout.flush()
            sys.stdout.write('\n')
        elif (type(files) is list):
            for file in files:
                if (not(type(file) is str)):
                    raise TypeError("Argument 'files' must be a list containing only str elements")
            print("File list found for extraction. Extracting only specified files.")
            filenum = 0
            totalFiles = len(files)
            for file in files:
                file = "./" + file
                UntarredFilePath = os.path.abspath("{0:s}/{1:s}".format(tarFileLocation, file))
                os.makedirs(os.path.dirname(UntarredFilePath), exist_ok=True)
                tarFileFolder.extract(file, path=tarFileLocation, set_attrs=True)
                filenum+=1
                sys.stdout.write('\r{}/{} files extracted     '.format(filenum, totalFiles))
                sys.stdout.flush()
            sys.stdout.write('\n')
        else:
            raise TypeError("Argument 'files' must be a list containing only str elements")
    if deleteTarFile:
        os.remove(tarFilePath)