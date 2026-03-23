
int FUN_00673670(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int local_8;
  
  if (param_1 != param_2) {
    do {
      local_8 = param_1;
      iVar3 = param_1 + 0x18;
      if (iVar3 == param_2) {
        return param_2;
      }
      cVar1 = FUN_00675be0(param_1,iVar3);
      param_1 = iVar3;
    } while (cVar1 == '\0');
    while (param_1 = param_1 + 0x18, param_1 != param_2) {
      cVar1 = FUN_00675be0(local_8,param_1);
      if (cVar1 == '\0') {
        local_8 = local_8 + 0x18;
        uVar2 = FUN_00417780(param_1);
        FUN_0045e0f0(uVar2);
      }
    }
    param_2 = local_8 + 0x18;
  }
  return param_2;
}

