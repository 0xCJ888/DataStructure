# big2

## Introduction
big2 is a CLI Taiwanese poker game using redis

## Library
Using hiredis in this program.

## Building big2
``` bash
make
```

## Running big2
```bash
./bin/big2
```

## Instructions
You run `./bin/big2`, and redis-server is running on background.<br>
First, deal 52 cards to four players.<br>
Second, determine list of pokers in player's hand.<br>
Final, terminal will show pokers in player's hand, pair, fullhouse, four of kind, straight and straight flush