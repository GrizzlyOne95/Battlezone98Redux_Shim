
void __fastcall FUN_00639680(int param_1)

{
  FUN_004f6aa0();
  if (*(int *)(param_1 + 0x114) < 0xc) {
    if (1 < *(int *)(param_1 + 0x114)) {
      FUN_004f6ab0("bd06001.otf",DAT_0091755c,0x41000000,0);
    }
  }
  else {
    FUN_004f6ab0("bd06001.otf",DAT_009175b0,0x41000000,0);
  }
  if (*(char *)(param_1 + 0x55) == '\0') {
    if (0xd < *(int *)(param_1 + 0x114)) {
      FUN_004f6ab0("bd06002.otf",DAT_0091755c,0x41000000,0);
    }
  }
  else {
    FUN_004f6ab0("bd06002.otf",DAT_009175b0,0x41000000,0);
  }
  return;
}

