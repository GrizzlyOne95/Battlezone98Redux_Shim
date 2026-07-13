
void FUN_0082d6fd(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x70);
  FUN_0082f92f(iVar1,*(undefined4 *)(iVar1 + 0x20));
  FUN_0083018d(iVar1,1);
  *(undefined4 *)(iVar1 + 0x74) = 0;
  do {
    *(undefined4 **)(iVar1 + 0x14) = *(undefined4 **)(iVar1 + 0x28);
    uVar2 = **(undefined4 **)(iVar1 + 0x28);
    *(undefined4 *)(iVar1 + 8) = uVar2;
    *(undefined4 *)(iVar1 + 0xc) = uVar2;
    *(undefined4 *)(iVar1 + 0x34) = 0;
    iVar3 = FUN_0082f4cb(iVar1,FUN_0082d55e,0);
  } while (iVar3 != 0);
  FUN_0082d56c(iVar1);
  return;
}

