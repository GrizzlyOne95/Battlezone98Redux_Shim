
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0061d120(undefined4 param_1,int param_2)

{
  uint local_8;
  
  if (DAT_008eaad8 != 5) {
    for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1) {
      if (*(int *)(&DAT_008ead18 + local_8 * 8) == param_2) {
        if (param_2 != DAT_02cecea0) {
          if (DAT_02cecea0 == 0x2a) {
            FUN_0061c0f0(param_1);
          }
          else if (DAT_02cecea0 != 8) {
            _DAT_02cebcd0 = DAT_02cecea0;
            DAT_02cebcd4 = DAT_02cecea4;
          }
          DAT_02cecea0 = *(int *)(&DAT_008ead18 + local_8 * 8);
          DAT_02cecea4 = (code *)(&PTR_FUN_008ead1c)[local_8 * 2];
        }
        (*DAT_02cecea4)(param_1);
        return;
      }
    }
  }
  return;
}

