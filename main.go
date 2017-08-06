package main

import (
	"gopkg.in/xtrade.v0/api"
	"fmt"
	"time"
)
func main(){
	api.Init()
	api.InitStore()
	as := api.GetStore()
	go func(as *api.Store) {
		var uapi *api.GoTraderAPI
		uapi = api.NewTraderAPI("tcp://180.168.146.187:10000", "9999", "your id", "your password")
		as.Set("099035", uapi)
		fmt.Printf("API store size:%d\n", as.Size())
		spi := api.NewTraderSPI()
		uapi.RegisterSpi(spi)
		uapi.RegisterFront()
		uapi.Connect()
		uapi.Join()
	}(as)
	time.Sleep(100 * time.Hour)
}