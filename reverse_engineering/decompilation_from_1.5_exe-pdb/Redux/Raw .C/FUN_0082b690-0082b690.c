
void FUN_0082b690(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_8;
  
  iVar2 = param_1;
  iVar4 = 1;
  if (1 < *(int *)(param_1 + 4)) {
    uVar1 = *(undefined4 *)(param_1 + 8);
    param_1 = FUN_0082cb3b(uVar1,0xffffffff);
    local_8 = -2;
    do {
      uVar3 = FUN_0082cb3b(uVar1,local_8);
      if (((*(int *)(iVar2 + 4) - iVar4) + 1 < 10) && (param_1 <= uVar3)) break;
      param_1 = param_1 + uVar3;
      iVar4 = iVar4 + 1;
      local_8 = local_8 + -1;
    } while (iVar4 < *(int *)(iVar2 + 4));
    FUN_0082c61c(uVar1,iVar4);
    *(int *)(iVar2 + 4) = *(int *)(iVar2 + 4) + (1 - iVar4);
  }
  return;
}

