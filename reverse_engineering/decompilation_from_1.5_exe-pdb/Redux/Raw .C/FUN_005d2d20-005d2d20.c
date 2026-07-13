
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005d2d20(void)

{
  longlong lVar1;
  uint uVar2;
  float10 fVar3;
  
  _DAT_00918308 = 1;
  _DAT_009182f0 = 1;
  DAT_009182f8 = DAT_009182d0;
  DAT_009182fc = DAT_009182d4;
  DAT_00918300 = DAT_009182c8;
  DAT_00918304 = DAT_009182cc;
  if (DAT_009182c8 < DAT_009182d0) {
    _DAT_00918308 = 0xffffffff;
    FUN_00592d60(&DAT_009182f8,&DAT_00918300);
  }
  if (DAT_009182cc < DAT_009182d4) {
    _DAT_009182f0 = 0xffffffff;
    FUN_00592d60(&DAT_009182fc,&DAT_00918304);
  }
  DAT_009182f8 = DAT_009182f8 - 0.01;
  DAT_009182fc = DAT_009182fc - 0.01;
  DAT_00918300 = DAT_00918300 + 0.01;
  DAT_00918304 = DAT_00918304 + 0.01;
  fVar3 = (float10)FUN_00461fd0(DAT_009182f8 * 0.1);
  DAT_009182f8 = (float)fVar3 * 10.0;
  fVar3 = (float10)FUN_00461fd0(DAT_009182fc * 0.1);
  DAT_009182fc = (float)fVar3 * 10.0;
  FUN_0043d610((DAT_00918300 - DAT_009182f8) * 0.1);
  DAT_009182dc = FUN_0083f040();
  FUN_0043d610((DAT_00918304 - DAT_009182fc) * 0.1);
  DAT_009182f4 = FUN_0083f040();
  DAT_00918300 = (float)DAT_009182dc * 10.0 + DAT_009182f8;
  DAT_00918304 = (float)DAT_009182f4 * 10.0 + DAT_009182fc;
  uVar2 = DAT_009182dc * DAT_009182f4;
  lVar1 = (ulonglong)uVar2 * 4;
  DAT_009182d8 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  memset(DAT_009182d8,0,uVar2 * 4);
  return;
}

