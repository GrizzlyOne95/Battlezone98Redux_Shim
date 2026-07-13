
void __fastcall FUN_004a0020(int param_1)

{
  undefined4 uVar1;
  uint local_c;
  
  FUN_0049f9e0();
  *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
  FUN_0047c070();
  *(undefined4 *)(param_1 + 0x1018) = 0xf149f2ca;
  *(undefined4 *)(param_1 + 0x188) = 0;
  for (local_c = 0; (int)local_c < 10; local_c = local_c + 1) {
    *(undefined4 *)(param_1 + 0xfc4 + local_c * 4) = 0;
  }
  memset((void *)(param_1 + 0x18c),0,0xe38);
  *(undefined4 *)(param_1 + 0x1014) = 0;
  DAT_0260d744 = FUN_0068bed0("menuunderlay");
  DAT_0260d730 = FUN_0068bed0("smenuunderlay");
  DAT_008e7c98 = FUN_0068bed0(PTR_s_key_SPC_008e7c94);
  DAT_008e797c = FUN_0068bed0(PTR_s_key_ALT_008e7978);
  DAT_008e7a08 = FUN_0068bed0(PTR_s_key_TAB_008e7a04);
  for (local_c = 0; local_c < 10; local_c = local_c + 1) {
    uVar1 = FUN_0068bed0((&PTR_s_key_1_008e7c00)[local_c * 2]);
    *(undefined4 *)(&DAT_008e7c04 + local_c * 8) = uVar1;
  }
  return;
}

