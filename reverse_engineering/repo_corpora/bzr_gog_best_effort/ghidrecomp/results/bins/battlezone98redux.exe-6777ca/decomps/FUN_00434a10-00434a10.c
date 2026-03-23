
undefined4 FUN_00434a10(undefined4 param_1,undefined4 param_2,int param_3)

{
  int local_8;
  
  if (param_3 != 0) {
    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
      *(undefined4 *)(param_3 + local_8 * 4) = *(undefined4 *)(&DAT_0260c244 + local_8 * 4);
      *(uint *)(&DAT_0260c244 + local_8 * 4) =
           ~*(uint *)(&DAT_0260c234 + local_8 * 4) & *(uint *)(&DAT_0260c244 + local_8 * 4);
      *(undefined4 *)(&DAT_0260c234 + local_8 * 4) = 0;
    }
  }
  return 0;
}

