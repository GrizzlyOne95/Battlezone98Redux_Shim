
int FUN_006a8c50(undefined4 param_1,int param_2,undefined4 param_3,int param_4,int *param_5,
                int *param_6)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int local_10;
  int local_c;
  
  local_10 = 0;
  bVar1 = false;
  local_c = 0;
  *param_5 = 0;
  while ((0 < param_4 && (!bVar1))) {
    iVar2 = FUN_0069d590(param_2 + 0xc,local_c);
    if (iVar2 == 0) {
      bVar1 = true;
    }
    else {
      iVar3 = (**(code **)(*param_6 + 0x20))(iVar2);
      if (iVar3 == 0) {
        local_c = local_c + 1;
      }
      else {
        FUN_006a8b30(param_2,iVar2,param_1);
        FUN_006a8ae0(param_3,iVar2,param_1);
        iVar2 = FUN_00694a90(iVar2,param_1);
        param_4 = param_4 - iVar2;
        local_10 = local_10 + iVar2;
        *param_5 = *param_5 + 1;
      }
    }
  }
  return local_10;
}

