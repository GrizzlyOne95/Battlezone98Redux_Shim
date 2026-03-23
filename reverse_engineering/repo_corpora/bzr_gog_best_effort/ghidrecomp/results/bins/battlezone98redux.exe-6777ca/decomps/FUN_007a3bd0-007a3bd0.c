
undefined4 __thiscall FUN_007a3bd0(undefined4 param_1,int param_2)

{
  undefined4 local_c;
  undefined4 local_8;
  
  if (param_2 < 0) {
    for (local_8 = 0; local_8 < -param_2; local_8 = local_8 + 0x78) {
      FUN_007a3130();
    }
  }
  else {
    for (local_c = 0; local_c < param_2; local_c = local_c + 0x78) {
      FUN_007a3110(param_1);
    }
  }
  return 1;
}

