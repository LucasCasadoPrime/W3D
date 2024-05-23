import os
import sys

def cleanDS_Store():
    for root, dirs, files in os.walk(os.getcwd()):
        for file in files:
            if file == '.DS_Store':
                os.remove(os.path.join(root, file))
                print('Deleted: ', os.path.join(root, file))

def main():
    cleanDS_Store()


if __name__ == '__main__':
    main()