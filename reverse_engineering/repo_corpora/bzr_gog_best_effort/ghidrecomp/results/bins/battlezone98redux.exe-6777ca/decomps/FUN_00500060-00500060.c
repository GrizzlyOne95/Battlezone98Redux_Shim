
undefined4 FUN_00500060(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_004ff750(param_1,1);
  iVar2 = FUN_00462630(uVar1);
  if ((iVar2 != 0) && (iVar2 = FUN_00417ca0(), iVar2 != 0)) {
    uVar1 = FUN_0082ba1c(param_1,2);
    iVar2 = FUN_00417f60(uVar1);
    if (iVar2 != 0) {
      FUN_0082cd08(param_1,*(int *)(iVar2 + 8) + 0x18,8);
      return 1;
    }
  }
  return 0;
}

