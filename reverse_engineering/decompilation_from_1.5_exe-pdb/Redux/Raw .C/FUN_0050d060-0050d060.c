
void __fastcall FUN_0050d060(undefined4 param_1)

{
  undefined4 uVar1;
  uint local_8;
  
  for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1) {
    uVar1 = FUN_0068bed0((&PTR_s_circ_1_008e8ba0)[local_8 * 2],param_1);
    *(undefined4 *)(&DAT_008e8ba4 + local_8 * 8) = uVar1;
  }
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    uVar1 = FUN_0068bed0((&PTR_s_circ_O_008e8b28)[local_8 * 4],param_1);
    *(undefined4 *)(&DAT_008e8b2c + local_8 * 0x10) = uVar1;
  }
  DAT_008e8bf8 = FUN_0068bed0(PTR_s_bignum_g___008e8bf4,param_1);
  DAT_00917f30 = FUN_0068bed0("mapunderlay");
  DAT_00917f2c = FUN_0068bed0("smapunderlay");
  return;
}

