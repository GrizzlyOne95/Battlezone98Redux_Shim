
undefined4 FUN_004aff40(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 local_c;
  int local_8;
  
  local_8 = FUN_00829130(param_1,&local_c);
  if (local_8 == 0) {
    if (DAT_009174e4 != 0) {
      uVar1 = FUN_00828cf0(param_1);
      FUN_004afe50("%s not found\n",uVar1);
    }
  }
  else {
    param_2 = FUN_004afde0(local_8,local_c,param_2);
    FUN_0062f240(local_8);
    if (DAT_009174e4 != 0) {
      uVar1 = FUN_008289a0(param_1);
      uVar1 = FUN_00828cf0(uVar1);
      FUN_004afe50("%s %08x (%s)\n",param_1,param_2,uVar1);
    }
  }
  return param_2;
}

