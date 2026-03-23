
undefined4 FUN_004ff460(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 local_14 [4];
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = FUN_0082c8f6(param_1);
  FUN_0082c82c(param_1,0xffffd8ee,"tostring");
  local_8 = 1;
  while( true ) {
    if (local_10 < local_8) {
      FUN_004ff3a0(&DAT_0087a44c);
      return 0;
    }
    FUN_0082cdd2(param_1,0xffffffff);
    FUN_0082cdd2(param_1,local_8);
    FUN_0082c585(param_1,1,1);
    local_c = FUN_0082d377(param_1,0xffffffff,local_14);
    if (local_c == 0) break;
    if (1 < local_8) {
      FUN_004ff3a0(&DAT_0087bd08);
    }
    FUN_004ff3a0(&DAT_00879854,local_c);
    FUN_0082d226(param_1,0xfffffffe);
    local_8 = local_8 + 1;
  }
  uVar1 = FUN_0082bc39(param_1,"\'tostring\' must return a string to \'print\'");
  return uVar1;
}

