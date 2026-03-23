
undefined4 __thiscall FUN_005cbdd0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00460fc0(param_2,param_1);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0x10);
  }
  return uVar2;
}

