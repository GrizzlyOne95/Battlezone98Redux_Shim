
undefined4 FUN_005008e0(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_004ff750(param_1,1);
  iVar2 = FUN_00462630(uVar1);
  if ((iVar2 == 0) || (*(int *)(iVar2 + 0xec) == 0)) {
    uVar1 = 0;
  }
  else {
    FUN_0082cd08(param_1,*(int *)(iVar2 + 0xec) + 0x30,8);
    uVar1 = 1;
  }
  return uVar1;
}

