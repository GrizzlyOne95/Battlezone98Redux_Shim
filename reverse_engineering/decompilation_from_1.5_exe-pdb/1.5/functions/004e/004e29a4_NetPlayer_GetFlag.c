/*
 * Entry: 004e29a4
 * Name: NetPlayer::GetFlag
 * Namespace: NetPlayer
 * Signature: void * GetFlag(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl NetPlayer::GetFlag(ushort param_1)

{
  NetPlayer *pNVar1;
  int iVar2;
  char *pcVar3;
  undefined2 in_stack_00000006;
  undefined4 local_8;
  
  local_8 = 0x100;
  pNVar1 = Find(param_1);
  if (pNVar1 == (NetPlayer *)0x0) {
LAB_004e29f5:
    pcVar3 = (char *)0x0;
  }
  else {
    if (pNVar1->bGotFlag == false) {
      iVar2 = dpGetPlayerData(Net::dp,_param_1,0xd,pNVar1->flagBuf,&local_8,0);
      if (iVar2 != 0) goto LAB_004e29f5;
      pNVar1->bGotFlag = true;
    }
    pcVar3 = pNVar1->flagBuf;
  }
  return pcVar3;
}
