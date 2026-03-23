
void __fastcall FUN_00587590(int param_1)

{
  undefined4 uVar1;
  int local_8;
  
  *(undefined4 *)(param_1 + 8) = 0xffff8300;
  *(undefined4 *)(param_1 + 0xc) = 0xffff8300;
  for (local_8 = 0; local_8 < 0x1d; local_8 = local_8 + 1) {
    uVar1 = FUN_0068bed0((&PTR_s_c_cross_008e8d18)[local_8 * 2]);
    *(undefined4 *)(&DAT_008e8d1c + local_8 * 8) = uVar1;
  }
  return;
}

