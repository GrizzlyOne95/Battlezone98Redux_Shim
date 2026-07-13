/*
 * Entry: 00550cce
 * Name: SyncGamePlayerList::Init
 * Namespace: SyncGamePlayerList
 * Signature: void Init(SyncGamePlayerList * this, HWND__ * param_1, dp_s * param_2, HWND__ * param_3, Chat * param_4, _func___cdecl_void_short_long_int * param_5, HWND__ * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
SyncGamePlayerList::Init
          (SyncGamePlayerList *this,HWND__ *param_1,dp_s *param_2,HWND__ *param_3,Chat *param_4,
          _func___cdecl_void_short_long_int *param_5,HWND__ *param_6)

{
  DWORD DVar1;
  
  PlayerList::Init((PlayerList *)this,param_1,param_2,param_3,param_4,param_5);
  this->hLaunchButton = param_6;
  DVar1 = Get_TimeNow();
  this->dwConnectStateSendTime = DVar1;
  return;
}
