
undefined4 FUN_005c9ec0(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    uVar2 = FUN_005c9dc0(uVar2,iVar1);
  }
  return uVar2;
}

