#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void FreeArray(int index, int *pFileCount, char **pFiles)
{
    *pFileCount -= 1;
    free(pFiles[index]);
    for (int counter = index; counter < *pFileCount; counter++)
    {
        pFiles[counter] = pFiles[counter + 1];
    }
    pFiles = (char **)realloc(pFiles, sizeof(char *) * (*pFileCount));
}

int main(int argc, char *argv[])
{
    FILE *pMakefile;
    DIR *currentDirectory;
    struct dirent *dir;
    int fileCount = 0;
    char *pPath = argv[1];
    char **pFileNames = (char **)malloc(sizeof(char *) * fileCount);

    currentDirectory = opendir(pPath);

    if (currentDirectory)
    {
        pMakefile = fopen("makefile", "w");

        while ((dir = readdir(currentDirectory)) != NULL)
        {
            fileCount += 1;
            pFileNames = (char **)realloc(pFileNames, sizeof(char *) * fileCount);
            pFileNames[fileCount - 1] = strdup(dir->d_name);
        }

        fprintf(pMakefile, "prog: ");

        for (int i = 0; i < fileCount; i++)
        {
            int length = strlen(pFileNames[i]);

            if (pFileNames[i][length - 1] == 'c' && pFileNames[i][length - 2] == '.')
            {
                char fileNameWithoutEnd[length - 2];
                strncpy(fileNameWithoutEnd, pFileNames[i], length - 2);
                fprintf(pMakefile, "build/%s.o ", fileNameWithoutEnd);
            }
            else
            {
                FreeArray(i, &fileCount, pFileNames);
                i--;
            }
        }

        fprintf(pMakefile, "\n\tgcc -o build/prog ");

        for (int i = 0; i < fileCount; i++)
        {
            int length = strlen(pFileNames[i]);
            char fileNameWithoutEnd[length - 2];
            strncpy(fileNameWithoutEnd, pFileNames[i], length - 2);
            fprintf(pMakefile, "build/%s.o ", fileNameWithoutEnd);
        }

        fprintf(pMakefile, "\n\n");

        for (int i = 0; i < fileCount; i++)
        {
            int length = strlen(pFileNames[i]);
            char fileNameWithoutEnd[length - 2];
            strncpy(fileNameWithoutEnd, pFileNames[i], length - 2);

            fprintf(pMakefile, "build/%s.o: %s | build\n\tgcc -c %s -o build/%s.o\n\n",
                    fileNameWithoutEnd, pFileNames[i], pFileNames[i], fileNameWithoutEnd);
        }

        fprintf(pMakefile, "build:\n\tmkdir -p build");

        fclose(pMakefile);
        closedir(currentDirectory);
    }
}