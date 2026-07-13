
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00621590(void)

{
  int iVar1;
  int local_8;
  
  iVar1 = FUN_004344a0();
  if (iVar1 == 2) {
    FUN_0041e870();
    FUN_004b72d0();
  }
  local_8 = DAT_0091a364;
  while (iVar1 = local_8 + -1, local_8 != 0) {
    local_8 = iVar1;
    if ((&DAT_0091a434)[iVar1] != 0) {
      (**(code **)((&DAT_0091fefc)[iVar1] + 0xc))(&DAT_0091ff10 + iVar1 * 0x74);
    }
  }
  _DAT_009198d4 = 0;
  _DAT_009198d8 = 0;
  _DAT_009198dc = 0;
  _DAT_009198e0 = 0;
  _DAT_009198e4 = 0;
  _DAT_009198e8 = 0;
  _DAT_009198ec = 0;
  _DAT_009198f0 = 0;
  memset(&DAT_0091989c,0,0x38);
  _DAT_0091a350 = 0;
  _DAT_0091a354 = 0;
  _DAT_0091a358 = 0;
  _DAT_0091a35c = 0;
  DAT_0091a430 = 0;
  DAT_0091a450 = 0;
  DAT_0091843c = 0;
  memset(&DAT_02a142e0,0,400);
  DAT_0091a44c = 0;
  _DAT_00920154 = 0;
  DAT_0091fef8 = 0;
  memset(&DAT_00919900,0,0xa50);
  memset(&DAT_00918440,0,0x410);
  memset(&DAT_0091a458,0,0x5aa0);
  DAT_0091a364 = 0;
  DAT_0091a434 = 0;
  DAT_0091a438 = 0;
  DAT_0091a43c = 0;
  DAT_0091a440 = 0;
  DAT_0091a444 = 0;
  memset(&DAT_0091a368,0,200);
  DAT_0091fefc = 0;
  DAT_0091ff00 = 0;
  DAT_0091ff04 = 0;
  DAT_0091ff08 = 0;
  DAT_0091ff0c = 0;
  memset(&DAT_0091ff10,0,0x244);
  return;
}

