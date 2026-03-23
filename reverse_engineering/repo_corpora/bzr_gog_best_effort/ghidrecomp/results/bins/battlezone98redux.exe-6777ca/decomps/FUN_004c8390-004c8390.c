
void __fastcall FUN_004c8390(int param_1)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0xe4) = 0xffbfbfbf;
  *(undefined4 *)(param_1 + 0xe0) = 0xff000000;
  FUN_00689a70(DAT_0091552c);
  uVar1 = FUN_0083f040();
  *(undefined4 *)(param_1 + 0xd8) = uVar1;
  *(undefined4 *)(param_1 + 0xdc) = 0x280;
  return;
}

