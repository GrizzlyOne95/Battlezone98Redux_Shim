
void __thiscall
FUN_00746510(int *param_1,undefined4 param_2,undefined4 param_3,char *param_4,int param_5)

{
  char cVar1;
  int iVar2;
  undefined1 local_14;
  undefined1 local_13;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*param_4 == '\x01') {
    if ((param_4[1] == '\0') && (param_5 == 10)) {
      memcpy(&local_14,param_4,10);
      local_13 = 1;
      iVar2 = FUN_007659f0();
      if (iVar2 != 0) {
        FUN_00759710(param_3,&local_14,10,1);
      }
    }
    else if ((param_4[1] == '\x01') &&
            ((param_5 == 10 && (cVar1 = (**(code **)(*param_1 + 0x60))(param_3), cVar1 != '\0')))) {
      FUN_007476a0();
    }
  }
  FUN_0083e885();
  return;
}

