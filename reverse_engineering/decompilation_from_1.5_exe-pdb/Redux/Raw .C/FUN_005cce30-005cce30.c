
undefined4 FUN_005cce30(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_c;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    return 0;
  }
  local_c = 0;
  uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
  iVar3 = FUN_00417e20(uVar2);
  if (iVar3 == 0) {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
    iVar3 = FUN_00462340(uVar2);
    if (iVar3 == 0) goto LAB_005ccead;
  }
  local_c = FUN_00462630(*(undefined4 *)(iVar1 + 0x22c));
LAB_005ccead:
  if (local_c == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00462380();
  }
  return uVar2;
}

