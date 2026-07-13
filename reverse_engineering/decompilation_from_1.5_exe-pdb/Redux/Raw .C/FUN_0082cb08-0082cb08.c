
void FUN_0082cb08(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)FUN_0082c4a6(param_1,param_2);
  iVar2 = FUN_00830fbd(param_1,*puVar1,*(int *)(param_1 + 8) + -0x10);
  if (iVar2 == 0) {
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10;
  }
  else {
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  }
  return;
}

