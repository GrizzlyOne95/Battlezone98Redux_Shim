
undefined4 FUN_0083cfa8(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  
  while( true ) {
    if (param_2 == -1) {
      return 0;
    }
    puVar1 = (undefined4 *)FUN_0083c410(param_1,param_2);
    if (((byte)*puVar1 & 0x3f) != 0x1b) break;
    param_2 = FUN_0083c3e8(param_1,param_2);
  }
  return 1;
}

