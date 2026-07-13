/*
 * Entry: 0055985e
 * Name: SyncGamePlayerList::SendStartState
 * Namespace: SyncGamePlayerList
 * Signature: void SendStartState(SyncGamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall SyncGamePlayerList::SendStartState(SyncGamePlayerList *this)

{
  ulong *puVar1;
  DWORD DVar2;
  Player *pPVar3;
  undefined2 local_58 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  DVar2 = Get_TimeNow();
  puVar1 = &this->dwConnectStateSendTime;
  if (DVar2 + 2000 < *puVar1) {
    *puVar1 = DVar2;
  }
  if (*puVar1 <= DVar2) {
    *puVar1 = DVar2 + 500;
    pPVar3 = PlayerList::FindPlayer((PlayerList *)this,Net::myPlayerID);
    if (pPVar3 != (Player *)0x0) {
      local_58[0] = 0x4c4e;
      if (pPVar3->launched == false) {
        local_58[0] = 0x6e6e;
      }
      dp_result = Net::Send((dp_s *)this->_padding_,Net::myPlayerID,0,0,local_58,4);
    }
  }
  return;
}
