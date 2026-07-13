
undefined4 FUN_005b08b0(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  uint local_8;
  
  if (param_3 != (uint *)0x0) {
    local_8 = (uint)(DAT_008e8f9c == 0);
    *param_3 = local_8 | 2;
    if (DAT_009181b8 == 1) {
      *param_3 = *param_3 | 4;
    }
  }
  return 0;
}

