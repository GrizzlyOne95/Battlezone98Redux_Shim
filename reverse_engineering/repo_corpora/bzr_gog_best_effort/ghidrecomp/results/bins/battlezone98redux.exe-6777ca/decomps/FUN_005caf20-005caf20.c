
void FUN_005caf20(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 != 0) {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
    iVar3 = FUN_00417e20(uVar2);
    if (iVar3 != 0) {
      *(undefined4 *)(*(int *)(iVar1 + 0x230) + 0xe0) = 1;
    }
  }
  return;
}

