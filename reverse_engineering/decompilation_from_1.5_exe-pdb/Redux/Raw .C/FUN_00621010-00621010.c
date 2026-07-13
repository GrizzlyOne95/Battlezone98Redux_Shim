
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00621010(void)

{
  int iVar1;
  
  iVar1 = FUN_004344a0();
  if (iVar1 == 2) {
    FUN_004b72d0();
    FUN_0041e860();
  }
  FUN_00620010();
  FUN_00620980();
  DAT_0091a44c = FUN_0061e1c0("keyboard");
  _DAT_00920154 = 0;
  if (0 < *(int *)(DAT_0094672c + 0x34)) {
    _DAT_00920154 = FUN_0061e1c0("joystick");
  }
  (**(code **)((&DAT_0091fefc)[DAT_0091a44c] + 0x1c))();
  DAT_009198fc = 0;
  DAT_009198f8 = 0;
  return;
}

