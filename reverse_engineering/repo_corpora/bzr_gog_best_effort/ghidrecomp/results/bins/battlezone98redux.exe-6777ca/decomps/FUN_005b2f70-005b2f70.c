
void __fastcall FUN_005b2f70(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_005c5ff0(*(undefined4 *)(param_1 + 0x374));
  *(undefined4 *)(param_1 + 0x370) = uVar1;
  if (-1 < *(int *)(param_1 + 0x370)) {
    FUN_005c6230(*(undefined4 *)(param_1 + 0x370));
    *(undefined4 *)(param_1 + 0x370) = 0xffffffff;
  }
  FUN_005afec0();
  return;
}

