package api

// #cgo CFLAGS: -std=c99
// #cgo LDFLAGS: -L${SRCDIR}/github.com/go-xtrade/xtrade/libs -lthosttraderapi
// #cgo LDFLAGS: -lstdc++
// #include "trade.h"
// #include <stdlib.h>
import "C"

//GoTraderAPI for api
type GoTraderAPI struct {
	TraderAPI  C.TraderAPI
	Spi        GoTraderSPI
	SessionID  int    //typedef int TThostFtdcSessionIDType;       //TFtdcSessionIDType是一个会话编号类型
	FrontID    int    //typedef int TThostFtdcFrontIDType;         //TFtdcFrontIDType是一个前置编号类型
	UserID     string //typedef char TThostFtdcUserIDType[16];     //TFtdcUserIDType是一个用户代码类型
	BrokerID   string //typedef char TThostFtdcBrokerIDType[11];   //TFtdcBrokerIDType是一个经纪公司代码类型
	SystemName string //typedef char TThostFtdcSystemNameType[41]; //TFtdcSystemNameType是一个系统名称类型
	FrontAddr  string //前置地址
	password   string //登录密码
}

// GoTraderSPI for api
type GoTraderSPI struct {
	TraderSPI C.TraderSPI
}

//GoCredential XXX
type GoCredential struct {
	Credential C.Credential
}

//NewTraderAPI trade api
func NewTraderAPI(frontAddr, brokerID, userID, password string) *GoTraderAPI {
	api := &GoTraderAPI{}
	api.TraderAPI = C.CreateCThostFtdcTraderApi()
	api.FrontAddr = frontAddr
	api.BrokerID = brokerID
	api.UserID = userID
	api.password = password
	return api
	// api.TraderAPI = C.CreateCThostFtdcTraderApi()
}

//NewTraderSPI spi
func NewTraderSPI() *GoTraderSPI {
	spi := &GoTraderSPI{}
	spi.TraderSPI = C.CTraderSpiInit()
	return spi
}

// func NewCredential(account, password string) *GoCredential {
// 	cred := &GoCredential{C.NewCredential(C.CString(account), C.CString(password))}
// 	return cred
// }

// func (api GoTraderAPI) UserLogin(account, password string) {
// 	var cred C.Credential = C.NewCredential(C.CString(account), C.CString(password))
// 	C.UserLogin(account, password)

// }

//RegisterSpi SPI
func (api GoTraderAPI) RegisterSpi(spi *GoTraderSPI) {
	C.SetRegisterSpiUserID(spi.TraderSPI, C.CString(api.UserID))
	C.RegisterSpi(api.TraderAPI, spi.TraderSPI)
}
func (api GoTraderAPI) RegisterFront() {
	C.RegisterFront(api.TraderAPI)
}
func (api GoTraderAPI) Connect() {
	C.CThostFtdcTraderApiInit(api.TraderAPI)
}
func (api GoTraderAPI) Release() {
	C.CThostFtdcTraderApiRelease(api.TraderAPI)
}

func (api GoTraderAPI) Join() {
	C.CThostFtdcTraderApiJoin(api.TraderAPI)
}
func (api GoTraderAPI) UserLogin() {
	var account *C.char = C.CString(api.UserID)
	var pwd *C.char = C.CString(api.password)
	C.UserLogin(api.TraderAPI, account, pwd)
}
