# MakefileCreator

Creating your own makefiles for multiple C files can be a tedious and time-consuming task. To simplify this process, I developed a makefile generator that automatically creates makefiles for you. At present, the generator does not support subdirectories.
To use the program, first compile it, then run it with the following command:
```
makefilecreator.exe <path to the files>
```

The makefile will be generated in the same directory as the provided path, which is also where the C files are located.
