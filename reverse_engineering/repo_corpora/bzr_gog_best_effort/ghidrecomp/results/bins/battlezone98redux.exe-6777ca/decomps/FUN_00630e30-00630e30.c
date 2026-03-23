
void __fastcall FUN_00630e30(int param_1)

{
  FUN_004f6aa0();
  if (*(char *)(param_1 + 0x55) == '\0') {
    FUN_004f6ab0("bd01001.otf",DAT_0091755c,0x41000000,0);
  }
  else {
    FUN_004f6ab0("bd01001.otf",DAT_009175b0,0x41000000,0);
  }
  if (*(char *)(param_1 + 0x65) != '\0') {
    if (*(char *)(param_1 + 0x56) == '\0') {
      FUN_004f6ab0("bd01002.otf",DAT_0091755c,0x41000000,0);
    }
    else {
      FUN_004f6ab0("bd01002.otf",DAT_009175b0,0x41000000,0);
    }
    if (*(char *)(param_1 + 0x67) != '\0') {
      if (*(char *)(param_1 + 0x57) == '\0') {
        FUN_004f6ab0("bd01003.otf",DAT_0091755c,0x41000000,0);
      }
      else {
        FUN_004f6ab0("bd01003.otf",DAT_009175b0,0x41000000,0);
      }
    }
  }
  return;
}

