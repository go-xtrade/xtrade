#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ThostFtdcUserApiStruct.h>
extern int count;
// void userLogin();
typedef void *TraderAPI;
typedef void *TraderSPI;
typedef void *Credential;
typedef struct CThostFtdcRspInfoField CThostFtdcRspInfoField;
typedef struct CThostFtdcRspUserLoginField CThostFtdcRspUserLoginField;
typedef struct Session Session;
TraderSPI CTraderSpiInit(); 
TraderAPI CreateCThostFtdcTraderApi();
void RegisterSpi(TraderAPI pTraderAPI, TraderSPI pTraderSPI);
void SubscribePublicTopic(TraderAPI pTraderAPI);
void SubscribePrivateTopic(TraderAPI pTraderAPI);
void RegisterFront(TraderAPI pTraderAPI);
void CThostFtdcTraderApiInit(TraderAPI pTraderAPI);
void CThostFtdcTraderApiJoin(TraderAPI pTraderAPI);
void CThostFtdcTraderApiRelease(TraderAPI pTraderAPI);
Credential NewCredential(char *account,char *passwd);
void UserLogin(TraderAPI pTraderAPI, char *account,char *passwd);
void foo();
void trade();
void SetRegisterSpiUserID(TraderSPI pTraderSPI,char *userId);
#ifdef __cplusplus
}
#endif