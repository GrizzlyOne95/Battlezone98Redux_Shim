
uint __fastcall FUN_005b8a40(int param_1)

{
  uint uVar1;
  float10 extraout_ST0;
  
  uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0x1c))();
  if ((float)extraout_ST0 < 0.95) {
    uVar1 = FUN_00602420();
  }
  else {
    *(undefined4 *)(param_1 + 0xc) = 0xd;
  }
  return uVar1 & 0xffffff00;
}

