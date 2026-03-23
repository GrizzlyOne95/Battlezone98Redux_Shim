
void FUN_005cab80(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462630(param_2);
  if (iVar1 != 0) {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    FUN_005caa20(param_1,uVar2);
  }
  return;
}

