
void __fastcall FUN_007b6970(undefined4 param_1)

{
  int iVar1;
  
  *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xffffff7f;
  iVar1 = FUN_007c3cc0(param_1);
  if (iVar1 != 0) {
    *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) | 0x80;
  }
  return;
}

