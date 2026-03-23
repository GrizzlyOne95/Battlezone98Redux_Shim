
undefined4 FUN_0069d0a0(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_006998c0(param_1,param_2);
  if (iVar1 == 0) {
    *param_3 = 0xffffffff;
    uVar2 = 0xffffffff;
  }
  else {
    *param_3 = 0;
    uVar2 = *(undefined4 *)(iVar1 + 0x1c);
  }
  return uVar2;
}

