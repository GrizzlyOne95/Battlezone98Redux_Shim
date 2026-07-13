
int FUN_006af850(SOCKET param_1,byte *param_2,int param_3,u_long *param_4,undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_1 == 0xffffffff) {
    FUN_006d8cf0(0x2719);
    iVar2 = -1;
  }
  else {
    FUN_006ae8d0();
    puVar3 = param_5;
    iVar2 = ioctlsocket(param_1,param_3,param_4);
    iVar2 = FUN_006d8d90(iVar2,puVar3);
    if (-1 < iVar2) {
      puVar3 = (undefined4 *)FUN_004fbb60();
      uVar1 = puVar3[1];
      *param_5 = *puVar3;
      param_5[1] = uVar1;
      if (param_3 == -0x7ffb9982) {
        if (*param_4 == 0) {
          *param_2 = *param_2 & 0xfc;
        }
        else {
          *param_2 = *param_2 | 1;
        }
      }
    }
  }
  return iVar2;
}

