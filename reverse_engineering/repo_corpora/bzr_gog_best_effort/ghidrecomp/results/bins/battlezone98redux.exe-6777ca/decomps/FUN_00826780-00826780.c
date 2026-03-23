
bool FUN_00826780(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  int local_8;
  
  if (param_1 == (char *)0x0) {
    bVar2 = false;
  }
  else {
    iVar1 = _strnicmp(param_1,"null",4);
    if (iVar1 == 0) {
      bVar2 = true;
    }
    else {
      local_8 = FUN_00481af0(param_1);
      if (local_8 != 0) {
        iVar1 = FUN_00481a60(param_1);
        iVar1 = iVar1 + local_8;
        local_8 = FUN_00826850(local_8,param_1,iVar1);
        if (local_8 != 0) {
          local_8 = FUN_00826170(local_8,param_2,param_3,param_4,param_1,1,iVar1);
        }
        FUN_00481990(param_1);
      }
      bVar2 = local_8 != 0;
    }
  }
  return bVar2;
}

