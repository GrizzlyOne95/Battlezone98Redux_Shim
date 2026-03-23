
void FUN_00676ea0(int param_1,int param_2,int param_3,undefined4 param_4,undefined1 param_5)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int local_8;
  
  iVar4 = param_2;
  while (iVar1 = param_2 * 2, local_8 = iVar1 + 2, local_8 < param_3) {
    cVar2 = FUN_00422f40(local_8 * 0x18 + param_1,(iVar1 + 1) * 0x18 + param_1);
    if (cVar2 != '\0') {
      local_8 = iVar1 + 1;
    }
    uVar3 = FUN_00417780(local_8 * 0x18 + param_1);
    FUN_0045e0f0(uVar3);
    param_2 = local_8;
  }
  if (local_8 == param_3) {
    uVar3 = FUN_00417780((param_3 + -1) * 0x18 + param_1,iVar4);
    FUN_0045e0f0(uVar3);
    param_2 = param_3 + -1;
  }
  uVar3 = FUN_00417780(param_4,param_5);
  FUN_006774d0(param_1,param_2,iVar4,uVar3);
  return;
}

