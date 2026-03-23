
void __fastcall FUN_007af3e0(undefined4 param_1)

{
  undefined1 uVar1;
  longlong lVar2;
  
  if (DAT_009455b0 == 0 && DAT_009455b4 == 0) {
    DAT_0260baa8 = (uint)*(byte *)(DAT_0094672c + 0x27);
  }
  lVar2 = FUN_00822ea0(param_1);
  DAT_009455b0 = (int)(lVar2 + 20000);
  DAT_009455b4 = (int)((ulonglong)(lVar2 + 20000) >> 0x20);
  uVar1 = FUN_007c3cc0();
  *(undefined1 *)(DAT_0094672c + 0x27) = uVar1;
  FUN_00680fe0();
  return;
}

