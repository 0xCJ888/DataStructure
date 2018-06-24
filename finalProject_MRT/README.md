# MRT route

## Build
```
make
```

## Run
``` 
./build/MRT <command>
<command> : <departure station no> <departure station Chinese>  <destination station no> <destination station Chinese>
```
Ex. 
 I want to search info from 徐匯中學 to 劍南路

```
./build/MRT O52 徐匯中學 BR15 劍南路
```
Then,
you will see Travel Path, Travel time, ticket price

```
Travel path
O52     徐匯中學
O51     三和國中
O50     三重國小
O12     大橋頭
O11     民權西路
O10     中山國小
O09     行天宮
O08     松江南京
G15     松江南京
G16     南京復興
BR11    南京復興
BR12    中山國中
BR13    松山機場
BR14    大直
BR15    劍南路

Travel time : 29.3 min

Single-Journey Ticket : NT$40
EasyCard/iPASS : NT$32
Senior, Charity and Companion Cards : NT$16
```