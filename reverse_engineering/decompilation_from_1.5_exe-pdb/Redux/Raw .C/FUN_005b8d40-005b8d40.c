
undefined4 * __thiscall FUN_005b8d40(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  uint local_c;
  
  FUN_0056aea0(param_2,param_3);
  *param_1 = RemoteDetonator::vftable;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    param_1[local_c + 0x38] = 0;
  }
  *(undefined1 *)(param_1 + 0x3c) = 0;
  return param_1;
}

