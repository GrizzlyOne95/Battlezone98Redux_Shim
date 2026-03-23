
int FUN_006af8f0(int param_1,fd_set *param_2,fd_set *param_3,fd_set *param_4,timeval *param_5,
                undefined4 *param_6)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  DWORD local_8;
  
  FUN_006ae8d0();
  if ((((param_2 == (fd_set *)0x0) && (param_3 == (fd_set *)0x0)) && (param_4 == (fd_set *)0x0)) &&
     (param_5 != (timeval *)0x0)) {
    local_8 = param_5->tv_sec * 1000 + param_5->tv_usec / 1000;
    if (local_8 == 0) {
      local_8 = 1;
    }
    Sleep(local_8);
    puVar2 = (undefined4 *)FUN_004fbb60();
    uVar1 = puVar2[1];
    *param_6 = *puVar2;
    param_6[1] = uVar1;
    iVar3 = 0;
  }
  else {
    if (((param_5 != (timeval *)0x0) && (param_5->tv_sec == 0)) &&
       ((0 < param_5->tv_usec && (param_5->tv_usec < 1000)))) {
      param_5->tv_usec = 1000;
    }
    puVar2 = param_6;
    iVar3 = select(param_1,param_2,param_3,param_4,param_5);
    iVar3 = FUN_006d8d90(iVar3,puVar2);
    if (-1 < iVar3) {
      puVar2 = (undefined4 *)FUN_004fbb60();
      uVar1 = puVar2[1];
      *param_6 = *puVar2;
      param_6[1] = uVar1;
    }
  }
  return iVar3;
}

