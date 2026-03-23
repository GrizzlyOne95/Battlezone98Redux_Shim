
undefined4 __thiscall FUN_005cc080(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462630(param_3,param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    uVar2 = FUN_005cc020(param_2,uVar2);
  }
  return uVar2;
}

