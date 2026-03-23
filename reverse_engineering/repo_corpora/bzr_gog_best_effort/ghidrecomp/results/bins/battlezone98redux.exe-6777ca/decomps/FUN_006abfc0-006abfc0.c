
void FUN_006abfc0(int *param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  WSADATA local_198;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  LOCK();
  iVar1 = *param_1;
  *param_1 = *param_1 + 1;
  UNLOCK();
  if (iVar1 == 0) {
    iVar1 = WSAStartup(CONCAT11(param_3,param_2),&local_198);
    LOCK();
    param_1[1] = iVar1;
    UNLOCK();
  }
  FUN_0083e885();
  return;
}

