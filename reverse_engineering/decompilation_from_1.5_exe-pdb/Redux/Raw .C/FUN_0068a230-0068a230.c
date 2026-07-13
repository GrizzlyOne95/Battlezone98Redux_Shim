
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0068a230(int param_1)

{
  memset(&DAT_02bf0428,0,0xd884);
  DAT_02bf042c = 0;
  _DAT_02ceb820 = 0xbf800000;
  DAT_02ceb81c = 0x3c23d70a;
  DAT_02bf0428 = ((param_1 + 2) % 0x18 << 3) / 0x18;
  FUN_0068a150();
  return;
}

