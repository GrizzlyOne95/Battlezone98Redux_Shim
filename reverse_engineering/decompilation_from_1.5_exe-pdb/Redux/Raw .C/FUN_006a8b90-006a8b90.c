
int FUN_006a8b90(undefined4 param_1,int param_2,undefined4 param_3,int param_4,int *param_5)

{
  bool bVar1;
  int iVar2;
  int local_c;
  
  local_c = 0;
  bVar1 = false;
  *param_5 = 0;
  while ((0 < param_4 && (!bVar1))) {
    iVar2 = FUN_0069d590(param_2 + 0xc,0);
    if (iVar2 == 0) {
      bVar1 = true;
    }
    else {
      FUN_006a8b30(param_2,iVar2,param_1);
      FUN_006a8ae0(param_3,iVar2,param_1);
      iVar2 = FUN_00694a90(iVar2,param_1);
      param_4 = param_4 - iVar2;
      local_c = local_c + iVar2;
      *param_5 = *param_5 + 1;
    }
  }
  return local_c;
}

