
int FUN_0082c907(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *local_8;
  
  uVar2 = FUN_0082c4a6(param_1,param_2,param_3,&local_8);
  iVar3 = FUN_0082c405(uVar2);
  if (iVar3 != 0) {
    puVar1 = *(undefined4 **)(param_1 + 8);
    *puVar1 = *local_8;
    puVar1[1] = local_8[1];
    puVar1[2] = local_8[2];
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  }
  return iVar3;
}

