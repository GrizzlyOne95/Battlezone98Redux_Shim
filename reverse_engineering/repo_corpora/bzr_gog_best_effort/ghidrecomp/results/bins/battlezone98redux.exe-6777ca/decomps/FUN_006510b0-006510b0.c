
void __fastcall FUN_006510b0(int param_1)

{
  char cVar1;
  
  FUN_004f6aa0();
  if (*(int *)(param_1 + 0x1d4) < 6) {
    if (3 < *(int *)(param_1 + 0x1d4)) {
      FUN_004f6ab0("ch04001.otf",DAT_0091755c,0x41000000,0);
    }
  }
  else {
    FUN_004f6ab0("ch04001.otf",DAT_009175b0,0x41000000,0);
  }
  if (*(int *)(param_1 + 0x1dc) == 0) {
    cVar1 = FUN_005cd750(*(undefined4 *)(param_1 + 0x6c));
    if (cVar1 == '\0') {
      FUN_004f6ab0("ch04004.otf",DAT_0091755c,0x41000000,0);
      goto LAB_00651188;
    }
  }
  FUN_004f6ab0("ch04004.otf",DAT_009175b0,0x41000000,0);
LAB_00651188:
  if (*(char *)(param_1 + 0x56) == '\0') {
    if (5 < *(int *)(param_1 + 0x1d4)) {
      FUN_004f6ab0("ch04002.otf",DAT_0091755c,0x41000000,0);
    }
  }
  else {
    FUN_004f6ab0("ch04002.otf",DAT_009175b0,0x41000000,0);
  }
  if (0xb < *(int *)(param_1 + 0x1d4)) {
    FUN_004f6ab0("ch04003.otf",DAT_0091755c,0x41000000,0);
  }
  return;
}

