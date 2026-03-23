
void __fastcall FUN_00631960(int param_1)

{
  FUN_004f6aa0();
  if (*(int *)(param_1 + 0xd4) < 0xd) {
    if (*(int *)(param_1 + 0xd4) < 6) {
      FUN_004f6ab0("bd02001.otf",DAT_0091755c,0x41000000,0);
    }
    else {
      FUN_004f6ab0("bd02001.otf",DAT_009175b0,0x41000000,0);
    }
    if (*(int *)(param_1 + 0xd4) < 10) {
      if (5 < *(int *)(param_1 + 0xd4)) {
        FUN_004f6ab0("bd02002.otf",DAT_0091755c,0x41000000,0);
      }
    }
    else {
      FUN_004f6ab0("bd02002.otf",DAT_009175b0,0x41000000,0);
    }
  }
  if (*(int *)(param_1 + 0xd4) < 0x12) {
    if (0xc < *(int *)(param_1 + 0xd4)) {
      FUN_004f6ab0("bd02003.otf",DAT_0091755c,0x41000000,0);
    }
  }
  else {
    FUN_004f6ab0("bd02003.otf",DAT_0091757c,0x41000000,0);
  }
  return;
}

