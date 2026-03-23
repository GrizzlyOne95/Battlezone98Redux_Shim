
void FUN_00786200(int param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined2 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_c = 0; local_c < param_4; local_c = local_c + 1) {
    for (local_8 = 0; local_8 < param_3; local_8 = local_8 + 1) {
      for (local_10 = 0; local_10 < 0x100; local_10 = local_10 + 1) {
        for (local_14 = 0; local_14 < 0x100; local_14 = local_14 + 1) {
          uVar1 = FUN_00785fe0(param_2,param_3,param_4,
                               (double)((float)(local_8 * 0x100 + local_14) * 0.5),
                               (double)((float)(local_c * 0x100 + local_10) * 0.5));
          *(undefined2 *)
           (param_1 +
           (local_10 * 0x100 + local_8 * 0x10000 + param_3 * 0x10000 * local_c + local_14) * 2) =
               uVar1;
        }
      }
    }
  }
  if (DAT_009454cc == 0) {
    FUN_00785c80();
  }
  return;
}

