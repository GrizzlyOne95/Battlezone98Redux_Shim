
int FUN_006ae9c0(SOCKET param_1,byte *param_2,char param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_28 [8];
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  u_long local_10;
  undefined2 local_c;
  undefined2 local_a;
  int local_8;
  
  local_8 = 0;
  if (param_1 != 0xffffffff) {
    if ((param_3 != '\0') && ((*param_2 & 8) != 0)) {
      local_c = 0;
      local_a = 0;
      FUN_004fbb60();
      FUN_006af470(param_1,param_2,0xffff,0x80,&local_c,4,local_18);
    }
    FUN_006ae8d0();
    puVar4 = param_4;
    iVar3 = closesocket(param_1);
    local_8 = FUN_006d8d90(iVar3,puVar4);
    if (local_8 != 0) {
      FUN_006d8cc0(0x2733,0);
      cVar2 = FUN_006ab920(param_4,local_20);
      if (cVar2 == '\0') {
        FUN_006d8cc0(0x4d5,0);
        cVar2 = FUN_006ab920(param_4,local_28);
        if (cVar2 == '\0') goto LAB_006aeade;
      }
      local_10 = 0;
      ioctlsocket(param_1,-0x7ffb9982,&local_10);
      *param_2 = *param_2 & 0xfc;
      FUN_006ae8d0();
      puVar4 = param_4;
      iVar3 = closesocket(param_1);
      local_8 = FUN_006d8d90(iVar3,puVar4);
    }
  }
LAB_006aeade:
  if (local_8 == 0) {
    puVar4 = (undefined4 *)FUN_004fbb60();
    uVar1 = puVar4[1];
    *param_4 = *puVar4;
    param_4[1] = uVar1;
  }
  return local_8;
}

