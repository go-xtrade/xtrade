package api

// #cgo CFLAGS: -std=c99
// #cgo LDFLAGS: -L${SRCDIR}/github.com/go-xtrade/xtrade/libs -lthosttraderapi
// #cgo LDFLAGS: -lstdc++
// #include "trade.h"
// #include <stdlib.h>
import "C"
import (
	"fmt"

	"gopkg.in/iconv.v1"
	log "gopkg.in/logger.v1"
)

var Xapi *GoTraderAPI

//FrontConnectedCallback 连接前置成功回调函数
//export FrontConnectedCallback
func FrontConnectedCallback(cuserID *C.char) {

	fmt.Println(GetStore().Size())
	userID := C.GoString(cuserID)
	userAPI := GetStore().Get(userID)
	log.Infof("用户:[%s]API连接前置成功,随后请求登录", userID)
	userAPI.UserLogin()
	//TODO 更新登录状态到Store
}

//export UserLoginCallback
func UserLoginCallback(pRspUserLogin *C.CThostFtdcRspUserLoginField, pRspInfo *C.CThostFtdcRspInfoField, nRequestID C.int, bIsLast C.int) {
	fmt.Printf("login success%v,%v\n", nRequestID, bIsLast)
	fmt.Printf("前置编号: %d\n", pRspUserLogin.FrontID)
	fmt.Printf("用户代码: %s\n", C.GoString(&pRspUserLogin.UserID[0]))
	fmt.Printf("最大报单引用: %s\n", C.GoString(&pRspUserLogin.MaxOrderRef[0]))
	fmt.Printf("响应错误码: %d\n", pRspInfo.ErrorID)

	cd, err := iconv.Open("utf-8", "gbk") // convert gbk to utf-8
	if err != nil {
		fmt.Println("iconv.Open failed!")
		return
	}
	defer cd.Close()

	errMsg := cd.ConvString(C.GoString(&pRspInfo.ErrorMsg[0]))

	fmt.Println(errMsg)
	fmt.Printf("响应错误信息: %s\n", errMsg)
	///获取当前交易日
	fmt.Printf("会话编号 : %d\n", pRspUserLogin.SessionID)
}

//export GetTraderAPI
func GetTraderAPI() C.TraderAPI {
	return Xapi.TraderAPI
}
func Init() {}
