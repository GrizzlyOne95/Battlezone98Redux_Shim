
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004930e0(int param_1)

{
  undefined4 uVar1;
  uint local_8;
  
  DAT_009173cc = FUN_0068bed0("radarunderlay");
  DAT_009173c8 = FUN_0068bed0("sradarunderlay");
  for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1) {
    uVar1 = FUN_0068bed0((&PTR_s_circ_1_008e7758)[local_8 * 2]);
    *(undefined4 *)(&DAT_008e775c + local_8 * 8) = uVar1;
  }
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    uVar1 = FUN_0068bed0((&PTR_s_circ_O_008e77c0)[local_8 * 4]);
    *(undefined4 *)(&DAT_008e77c4 + local_8 * 0x10) = uVar1;
  }
  for (local_8 = 0; local_8 < 0xe; local_8 = local_8 + 1) {
    uVar1 = FUN_0068bed0((&PTR_s_ping_0_008e7838)[local_8 * 4]);
    *(undefined4 *)(&DAT_008e7840 + local_8 * 0x10) = uVar1;
  }
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    uVar1 = FUN_0068bed0((&PTR_s_compas_E_008e7734)[local_8 * 2]);
    *(undefined4 *)(&DAT_008e7738 + local_8 * 8) = uVar1;
  }
  *(undefined4 *)(param_1 + 0x70) = 0;
  _DAT_009173d0 = 0xf149f2ca;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x20090) = 0;
  *(undefined4 *)(param_1 + 0x20094) = 200;
  return;
}

