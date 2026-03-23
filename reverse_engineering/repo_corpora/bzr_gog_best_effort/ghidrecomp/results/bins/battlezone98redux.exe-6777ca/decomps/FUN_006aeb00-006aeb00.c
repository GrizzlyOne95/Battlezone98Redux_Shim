
undefined4 FUN_006aeb00(SOCKET param_1,byte *param_2,char param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  uint local_c;
  uint local_8;
  
  if (param_1 == 0xffffffff) {
    FUN_006d8cf0(0x2719);
    uVar1 = 0;
  }
  else if ((param_3 == '\0') && ((*param_2 & 1) != 0)) {
    FUN_006d8cf0(0x2726);
    uVar1 = 0;
  }
  else {
    FUN_006ae8d0();
    local_8 = (uint)(param_3 != '\0');
    local_c = local_8;
    puVar3 = param_4;
    iVar2 = ioctlsocket(param_1,-0x7ffb9982,&local_c);
    iVar2 = FUN_006d8d90(iVar2,puVar3);
    if (iVar2 < 0) {
      uVar1 = 0;
    }
    else {
      puVar3 = (undefined4 *)FUN_004fbb60();
      uVar1 = puVar3[1];
      *param_4 = *puVar3;
      param_4[1] = uVar1;
      if (param_3 == '\0') {
        *param_2 = *param_2 & 0xfd;
      }
      else {
        *param_2 = *param_2 | 2;
      }
      uVar1 = 1;
    }
  }
  return uVar1;
}

