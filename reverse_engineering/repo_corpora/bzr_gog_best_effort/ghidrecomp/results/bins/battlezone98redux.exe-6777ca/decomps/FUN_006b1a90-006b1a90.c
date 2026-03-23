
void FUN_006b1a90(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 char param_5,undefined4 param_6)

{
  char cVar1;
  int iVar2;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  
  FUN_004178a0(param_1);
  FUN_006acd10();
  if (param_5 == '\0') {
    cVar1 = FUN_006b1390(param_1);
    if (cVar1 == '\0') {
      FUN_006ad8c0(param_6,0x2719,0);
    }
    else {
      local_10 = 0;
      local_14 = param_4;
      iVar2 = WSARecv(*param_1,param_2,param_3,&local_10,&local_14,param_6,0);
      local_c = WSAGetLastError();
      if (local_c == 0x40) {
        local_c = 0x2746;
      }
      else if (local_c == 0x4d2) {
        local_c = 0x274d;
      }
      if ((iVar2 == 0) || (local_c == 0x3e5)) {
        FUN_006ad810(param_6);
      }
      else {
        FUN_006ad8c0(param_6,local_c,local_10);
      }
    }
  }
  else {
    FUN_006ad8c0(param_6,0,0);
  }
  return;
}

