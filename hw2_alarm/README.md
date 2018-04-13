# MultiAlarm
[![Build Status](https://travis-ci.org/ciaojhen/DataStructure.svg?branch=master)](https://travis-ci.org/ciaojhen/DataStructure)

## Introduction
This is a code by using linked list to set multiple alarm clock with libev
## Build 
```bash 
cd hw2_alarm
make
```

## Run
```bash
bin\alarm
```

## Set Timer
1. choose mode 
    > [1] Insert alarm <br>
    > [2] Delete alarm <br>
    > [3] Dump <br>
    > [4] Update <br>
    > [5] Quit
2. mode [1]
    > input time that you want to add and repeat or not
3. mode [2]
    > input timer name to delete
4. mode [3]
    > you can view alarm clock list sort by setting time
5. mode [4]
    > you can modify alarm<br>(delete last alarm on alarm list and add a new one )
6. mode [5]
    > Quit!