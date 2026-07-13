/*
 * Entry: 0055cd79
 * Name: ServerList::Timer
 * Namespace: ServerList
 * Signature: void Timer(ServerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ServerList::Timer(ServerList *this)

{
  UINT_PTR UVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  undefined1 local_240 [4];
  undefined1 local_23c [4];
  undefined4 local_238;
  undefined1 local_234 [116];
  undefined1 local_1c0 [184];
  char local_108 [33];
  undefined1 local_e7 [223];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1c0;
  if (this->iTimerID != 0) {
    KillTimer((HWND)this->hParent,this->iTimerID);
    this->iTimerID = 0;
  }
  iVar3 = 0;
  do {
    local_238 = 300;
    dp_result = dpReceive(Net::dp,local_23c,local_240,0,local_234,&local_238);
    if (dp_result == 0) {
      iVar3 = 0;
    }
    else {
      if (dp_result != 2) {
        pcVar2 = "Problem with internet connection";
        pcVar4 = local_108;
        for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined4 *)pcVar4 = *(undefined4 *)pcVar2;
          pcVar2 = pcVar2 + 4;
          pcVar4 = pcVar4 + 4;
        }
        *pcVar4 = *pcVar2;
        memset(local_e7,0,0xdf);
        read_text_label("multi_error","problem_internet",local_108);
        do_error(this->hParent,local_108);
        return;
      }
      iVar3 = iVar3 + 1;
    }
  } while (iVar3 < 3);
  if (this->bInEnumServers == false) {
    StartEnum(this);
    iVar3 = dpEnumServersEx(this->dp,this->enumDelay,Net::session_type,dpEnumServersCallback,this);
    if (iVar3 != 0) {
      EndEnum(this);
    }
  }
  UVar1 = SetTimer((HWND)this->hParent,1,100,(TIMERPROC)0x0);
  this->iTimerID = UVar1;
  return;
}
