
void __fastcall FUN_00493250(undefined4 param_1)

{
  uint local_8;
  
  FUN_00492ec0(DAT_02cecee4,param_1);
  DAT_0260d718 = DAT_0091757c;
  DAT_0260d71c = DAT_0091755c;
  DAT_0260d720 = DAT_00917560;
  DAT_0260d724 = DAT_009175b0;
  DAT_0260d728 = DAT_0091757c;
  DAT_0260d72c = DAT_00917588;
  for (local_8 = 0; local_8 < 0xe; local_8 = local_8 + 1) {
    *(uint *)(&DAT_008e7844 + local_8 * 0x10) =
         *(int *)(&DAT_008e783c + local_8 * 0x10) << 0x1c | 0xff00;
  }
  return;
}

