# XTrade [![Build Status](https://travis-ci.org/go-xtrade/xtrade.svg?branch=master)](https://travis-ci.org/go-xtrade/xtrade)
SimNow go API
## 启动
- 将动态链接库文件(.so) 重命名为 libthosttraderapi.so
- copy *.so到 /usr/loca/lib/下
或者指定动态库地址

```
LD_LIBRARY_PATH=./libs ./go-xtrade
```
示例：

```go
package main

import (
	"gopkg.in/xtrade.v0/api"
	"fmt"
	"time"
)

func main() {
	api.Init()
	api.InitStore()
	as := api.GetStore()
	go func(as *api.Store) {
		var uapi *api.GoTraderAPI
		uapi = api.NewTraderAPI("tcp://180.168.146.187:10000", "9999", "<your accout 1>", "your password")
		as.Set("your accout 1", uapi)
		fmt.Printf("API store size:%d\n", as.Size())
		spi := api.NewTraderSPI()
		uapi.RegisterSpi(spi)
		uapi.RegisterFront()
		uapi.Connect()
		uapi.Join()
	}(as)
	go func(as *api.Store) {
		var uapi *api.GoTraderAPI
		uapi = api.NewTraderAPI("tcp://180.168.146.187:10001", "9999", "<your accout 2>", "your password")
		as.Set("your accout 2", uapi)
		fmt.Printf("API store size:%d\n", as.Size())
		spi := api.NewTraderSPI()
		uapi.RegisterSpi(spi)
		uapi.RegisterFront()
		uapi.Connect()
		uapi.Join()
	}(as)
	time.Sleep(100 * time.Hour)
}

```
