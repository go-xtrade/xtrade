package api

import (
	"sync"
)

//UserAPIStore 会话存储 内存
type UserAPIStore interface {
	// Sid() string
	Set(key string, session *GoTraderAPI)
	Get(string) GoTraderAPI
	Destroy() error
}

//Session 会话管理
type Session struct {
	ID         int    //typedef int TThostFtdcSessionIDType;       //TFtdcSessionIDType是一个会话编号类型
	FrontID    int    //typedef int TThostFtdcFrontIDType;         //TFtdcFrontIDType是一个前置编号类型
	UserID     string //typedef char TThostFtdcUserIDType[16];     //TFtdcUserIDType是一个用户代码类型
	BrokerID   string //typedef char TThostFtdcBrokerIDType[11];   //TFtdcBrokerIDType是一个经纪公司代码类型
	SystemName string //typedef char TThostFtdcSystemNameType[41]; //TFtdcSystemNameType是一个系统名称类型
}

//Store map
type Store struct {
	APIs map[string]*GoTraderAPI
	lock *sync.RWMutex
}

//Sid 存储API 关键key 用户ID 投资者代码
// func (apiStore *Store) Sid() string {
// 	return apiStore.UserID
// }

func (as *Store) Lock() {
	as.lock.Lock()
}

func (as *Store) Unlock() {
	as.lock.Unlock()
}
func (as *Store) RLock() {
	as.lock.RLock()
}
func (as *Store) RUnlock() {
	as.lock.RUnlock()
}

//Get API
func (as *Store) Get(key string) *GoTraderAPI {
	as.RLock()
	defer as.RUnlock()
	return as.APIs[key]
}

//Set lock api instance to store
func (as *Store) Set(key string, session *GoTraderAPI) {
	as.Lock()
	defer as.Unlock()
	as.APIs[key] = session
}

//Size API
func (as Store) Size() int {
	// as.RLock()
	// defer as.RUnlock()
	return len(as.APIs)
}

var apiStore *Store

func InitStore() {
	apiStore = &Store{}
	apiStore.APIs = make(map[string]*GoTraderAPI)
	apiStore.lock = &sync.RWMutex{}
}
func GetStore() *Store {
	return apiStore
}
