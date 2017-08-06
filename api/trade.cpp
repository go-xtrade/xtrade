#include <ThostFtdcTraderApi.h>
#include "CTraderSpi.hpp"
#include "trade.h"
#include <_cgo_export.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
typedef struct
{
  TThostFtdcInvestorIDType *account;
  TThostFtdcPasswordType *password;
} CCredential;
// UserApi对象
CThostFtdcTraderApi *pUserApi;

char FRONT_ADDR[] = "tcp://180.168.146.187:10000"; // 前置地址
// char  FRONT_ADDR[] = "tcp://218.202.237.33:10002";		 // 前置地址
// char  FRONT_ADDR[] = "tcp://180.168.146.187:10030";		 // 前置地址
TThostFtdcBrokerIDType BROKER_ID = "9999"; // 经纪公司代码

TThostFtdcInvestorIDType INVESTOR_ID = "099035"; // 注意输入你自己的simnow仿真投资者代码
// TThostFtdcPasswordType  PASSWORD = "371524136";			   // 注意输入你自己的simnow仿真用户密码

// TThostFtdcInvestorIDType INVESTOR_ID = "098841";			 // 注意输入你自己的simnow仿真投资者代码
TThostFtdcPasswordType PASSWORD = "371524136"; // 注意输入你自己的simnow仿真用户密码

TThostFtdcInstrumentIDType INSTRUMENT_ID = "rb1805";   // 合约代码 ，注意与时俱进改变合约ID,避免使用过时合约
TThostFtdcDirectionType DIRECTION = THOST_FTDC_D_Sell; // 买卖方向
TThostFtdcPriceType LIMIT_PRICE = 15170;               // 价格

// 请求编号
int iRequestID = 0;

int count = 6;
extern CTraderSpi *pUserSpi;
void foo()
{
  printf("foo\n");
}

void UserLogin(TraderAPI pTraderAPI, char *account, char *password)
{
  pUserApi = (CThostFtdcTraderApi *)pTraderAPI;
  // CCredential *cred = (CCredential *)pCred;
  CThostFtdcReqUserLoginField req;
  memset(&req, 0, sizeof(req));
  strcpy(req.BrokerID, BROKER_ID);
  // strcpy(req.UserID, INVESTOR_ID);
  // strcpy(req.Password, PASSWORD);
  cerr << "--->>> 发送用户登录请求: " << account << "xx" << password << endl;
  strcpy(req.UserID, account);
  strcpy(req.Password, password);
  int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
  cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}
void trade()
{
  // 初始化UserApi
  pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建UserApi
  CTraderSpi *pUserSpi = new CTraderSpi();
  pUserApi->RegisterSpi((CThostFtdcTraderSpi *)pUserSpi); // 注册事件类
  pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);     // 注册公有流
  pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);    // 注册私有流
  pUserApi->RegisterFront(FRONT_ADDR);                    // connect
  pUserApi->Init();

  pUserApi->Join();
  //	pUserApi->Release();
}
TraderSPI CTraderSpiInit()
{
  CTraderSpi *pCTraderSpi = new CTraderSpi();
  return (void *)pCTraderSpi;
}
TraderAPI CreateCThostFtdcTraderApi()
{
  CThostFtdcTraderApi *pCTrderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
  return (void *)pCTrderApi;
}
// Credential NewCredential(char *account, char *password)
// {
//   cerr << "--->>> 用户凭证: " << account << endl;
//   TThostFtdcInvestorIDType iAccount;
//   TThostFtdcPasswordType iPwd;

//   memset(&iAccount, 0, sizeof(iAccount));
//   memset(&iPwd, 0, sizeof(iPwd));

//   strcpy(iAccount, account);
//   // iAccount[12]='\0';iAccount
//   strcpy(iPwd, password);
//   // iPwd[40]="\0";

//   CCredential cred = {&iAccount, &iPwd};
//   // strcpy(account, cred->account);
//   // strcpy(req.Password, cred->password);
//   // TThostFtdcInvestorIDType iAccount = account;
//   // TThostFtdcPasswordType iPwd = (TThostFtdcPasswordType *)password;
//   // CCredential cred = {
//   //   *iAccount,
//   //   *iPwd
//   // }

//   return (void *)&cred;
// }
void RegisterSpi(TraderAPI pTraderAPI, TraderSPI pTraderSPI)
{
  CThostFtdcTraderApi *pCTraderAPI = (CThostFtdcTraderApi *)pTraderAPI;
  CTraderSpi *pCTraderSPI = (CTraderSpi *)pTraderSPI;
  pCTraderAPI->RegisterSpi((CThostFtdcTraderSpi *)pCTraderSPI);
}
void SubscribePublicTopic(TraderAPI *pTraderAPI)
{
  CThostFtdcTraderApi *pCTraderAPI = (CThostFtdcTraderApi *)pTraderAPI;
  pCTraderAPI->SubscribePublicTopic(THOST_TERT_RESTART);
}
void SubscribePrivateTopic(TraderAPI pTraderAPI)
{
  CThostFtdcTraderApi *pCTraderAPI = (CThostFtdcTraderApi *)pTraderAPI;
  pCTraderAPI->SubscribePrivateTopic(THOST_TERT_RESTART);
}
void RegisterFront(TraderAPI pTraderAPI)
{
  CThostFtdcTraderApi *pCTraderAPI = (CThostFtdcTraderApi *)pTraderAPI;
  pCTraderAPI->RegisterFront(FRONT_ADDR); //connect 前置机
}
void CThostFtdcTraderApiInit(TraderAPI pTraderAPI)
{
  CThostFtdcTraderApi *pCTraderAPI = (CThostFtdcTraderApi *)pTraderAPI;
  pCTraderAPI->Init();
}
void CThostFtdcTraderApiJoin(TraderAPI pTraderAPI)
{
  CThostFtdcTraderApi *pCTraderAPI = (CThostFtdcTraderApi *)pTraderAPI;
  pCTraderAPI->Join();
}
void CThostFtdcTraderApiRelease(TraderAPI pTraderAPI)
{
  CThostFtdcTraderApi *pCTraderAPI = (CThostFtdcTraderApi *)pTraderAPI;
  pCTraderAPI->Release();
}

void SetRegisterSpiUserID(TraderSPI pTraderSPI, char *userId){
  CTraderSpi *pCTraderSPI = (CTraderSpi *)pTraderSPI;
  pCTraderSPI->SetUserID(userId);
}
// int main(void){
//   	// 初始化UserApi
// 	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
// 	CTraderSpi* pUserSpi = new CTraderSpi();
// 	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
// 	pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);					// 注册公有流
// 	pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);				// 注册私有流
// 	pUserApi->RegisterFront(FRONT_ADDR);							// connect
// 	pUserApi->Init();

// 	pUserApi->Join();
// //	pUserApi->Release();
// }