
void FUN_0082ce65(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)FUN_0082c4a6(param_1,param_2);
  puVar2 = (undefined4 *)FUN_00830de6(*puVar2,*(int *)(param_1 + 8) + -0x10);
  iVar1 = *(int *)(param_1 + 8);
  *(undefined4 *)(iVar1 + -0x10) = *puVar2;
  *(undefined4 *)(iVar1 + -0xc) = puVar2[1];
  *(undefined4 *)(iVar1 + -8) = puVar2[2];
  return;
}

