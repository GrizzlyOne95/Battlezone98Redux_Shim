
uint __thiscall FUN_006131e0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  
  uVar1 = FUN_006130a0(param_2,param_3,param_1);
  if (((int)uVar1 < 0) || (4 < (int)uVar1)) {
    uVar1 = uVar1 & 0xffffff00;
  }
  else {
    uVar1 = FUN_00612f10(param_2,param_3,uVar1);
  }
  return uVar1;
}

