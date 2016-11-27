# Linux system monitor

- **Introduction**
- **Requirements**
- **The project**
- **The implementation**
- **How to compile**
- **Tests**
- **Bugs**
- **About the group**

### Introduction

This project was started because our teacher Ivanovitch chalenged my group to create a linux system monitor better than the default linux system monitor. The limit date to show to Ivanovitch this monitor was 11/28/2016.

### Requirements

- acpi;
-- sudo apt-get install acpi
- QTStudio;
- Ubuntu 14.04 or newer;


### O projeto

This monitor should mount a chart of process that have this metrics: cpu, thread, memory and average (average of thread, memory and cpu). This monitor should be able to kill process by pid. Another functionalits is cpu cores usage, RAM memory usage, SWAP memory usage and energy percentage of battery. This project is under development and probably have bugs.
As language we used C++ to create the logic and XML to create the UI.

### The implementation

We used the QTStudio as IDE to help our productivity, DEBUG and compilatiom of code. The code read this files to get the necessary informations:

|  data type      |            what to read          |
|-----------------|----------------------------------|
|  process data   |  "/proc/[0-9]/stat"              |
|  memory data    |  "/proc/meminfo" and "free -m"   |
|  CPU usage data |  "/proc/sat" and "nproc"         |
|  energy data    |  "acpi -b"                       |

### How to compile

To compile add the folder LinuxSystemonitor to QTStudio.
Now configure the file mainwindow.cpp :
- go to line 35 of this file and delete the string: "/home/nalbert/programacao/c++/projetosC++/TesteWeb/index.html";
- now in the place of this string put: "/home/<USER_NAME>/<PATH_TO_FOLDER_LinuxSystemonitor>/index.html";
- now open the file JsonCreator, go to line 39 and delete the string: "/home/nalbert/programacao/c++/projetosC++/TesteWeb/processos.json";
- Now in the place of this string put: "/home/<USER_NAME>/<PATH_TO_FOLDER_LinuxSystemonitor>/processos.html";
- "index.html" is the html where run the json file of the process chart, and "processos.json" are the json with the infomations of the process of the computer;

### Testes realizados

We used GDB to discover thee cause of same exceptions and used a "user test" where someone that isn't a developer of this project use the software.

### Bugs

The bugs are not too much and going to be fixed soon:
- The CPU chat don't show the rigth CPU usage;
- The chat of batery time to discharge doesn't show the time if the acpi is'nt configured on the linux;

### About the group

|  developer                    |  Nalbert Gabriel Melo Leal        |
|-------------------------------|-----------------------------------|
|  GitHub                       |  github.com/nalbertg              |
|  Bitbucket                    |  bitbucket.org/nalbertg/gremlins  |
|  personal email               |  nalbertrn@yahoo.com.br           |
|  academic/profissional email  |  nalbertg@outlook.com             |

|  developer                    |  Juliana Barbosa                    |
|-------------------------------|-------------------------------------|
|  GitHub                       |  github.com/julianaabs              |
|  Bitbucket                    |  https://bitbucket.org/julianaabs/  |
|  personal email               |  -                                  |
|  academic/profissional email  |  -                                  |








