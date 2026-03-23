
undefined4 FUN_005cd980(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    uVar2 = FUN_005cd820(uVar2,iVar1,param_2);
  }
  return uVar2;
}

