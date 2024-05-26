import os
import sys

def cleanDS_Store():
    for root, dirs, files in os.walk(os.getcwd()):

        for file in files:
            if file == '.DS_Store' or file == 'play.out':
                os.remove(os.path.join(root, file))
                print('Deleted File: ', os.path.join(root, file))

        for dir in dirs:
            if dir == 'play.out.dSYM':
                os.system('rm -rf {}'.format(os.path.join(root, dir)))
                print('Deleted Folder: {}'.format(os.path.join(root, dir)))
            

def main():
    cleanDS_Store()


if __name__ == '__main__':
    main()