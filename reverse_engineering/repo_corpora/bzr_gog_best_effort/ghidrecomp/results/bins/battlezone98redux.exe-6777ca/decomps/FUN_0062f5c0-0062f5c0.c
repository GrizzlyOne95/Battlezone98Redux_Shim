
void FUN_0062f5c0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x88);
  uVar1 = FUN_0062e250(param_1,0x28);
  *(undefined4 *)(iVar2 + 0xfc) = uVar1;
  iVar2 = FUN_0062dfe0(param_1);
  if (iVar2 != 0) {
    FUN_0061a140(1);
  }
  return;
}

