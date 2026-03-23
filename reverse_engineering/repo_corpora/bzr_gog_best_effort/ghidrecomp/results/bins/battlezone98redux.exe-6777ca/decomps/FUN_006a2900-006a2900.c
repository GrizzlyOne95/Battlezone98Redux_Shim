
CDC * __fastcall FUN_006a2900(CDC *param_1)

{
  CDC::CDC(param_1);
  *(undefined ***)param_1 = FindSendPoints::vftable;
  DAT_009310a8 = 0;
  *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
  DAT_00920c9b = 1;
  return param_1;
}

