
void __fastcall FUN_004f71b0(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  FUN_005e0bc0(2);
  if (*(char *)(param_1 + 0x65) == '\0') {
    iVar1 = FUN_005e0fd0(1,4);
    if (iVar1 == -1) {
      iVar1 = FUN_005e0fd0(5,0xe);
      if (iVar1 == -1) {
        iVar1 = FUN_005e0fd0(0xf,0x18);
        if (iVar1 == -1) {
          *(undefined1 *)(param_1 + 0x65) = 1;
          FUN_004f6aa0();
          FUN_004f6ab0(*(undefined4 *)(param_1 + 0x8c),DAT_009175b0,0x41000000,0);
          fVar2 = (float10)FUN_00822d80(*(undefined4 *)(param_1 + 0x84));
          FUN_0045c110((float)fVar2 + 5.0);
        }
      }
    }
  }
  if ((*(int *)(param_1 + 0x9c) == 1) && (*(char *)(param_1 + 0x65) == '\0')) {
    iVar1 = FUN_005e0fd0(1,4);
    if (iVar1 == -1) {
      *(undefined1 *)(param_1 + 0x65) = 1;
      FUN_004f6aa0();
      FUN_004f6ab0(*(undefined4 *)(param_1 + 0x8c),DAT_009175b0,0x41000000,0);
      fVar2 = (float10)FUN_00822d80(*(undefined4 *)(param_1 + 0x84));
      FUN_0045c110((float)fVar2 + 5.0);
    }
  }
  FUN_005e0bc0(1);
  if ((*(int *)(param_1 + 0x98) == 1) && (*(char *)(param_1 + 0x65) == '\0')) {
    iVar1 = FUN_005e0fd0(1,4);
    if (iVar1 == -1) {
      *(undefined1 *)(param_1 + 0x65) = 1;
      FUN_004f6aa0();
      FUN_004f6ab0(*(undefined4 *)(param_1 + 0x8c),DAT_0091757c,0x41000000,0);
      fVar2 = (float10)FUN_00822d80(*(undefined4 *)(param_1 + 0x88));
      FUN_0045c0f0((float)fVar2 + 5.0);
    }
  }
  if (*(char *)(param_1 + 0x65) == '\0') {
    iVar1 = FUN_004f6b10();
    if (((iVar1 < 1) && (*(char *)(param_1 + 0x66) == '\x01')) && (*(int *)(param_1 + 0x94) == 0)) {
      *(undefined1 *)(param_1 + 0x65) = 1;
      FUN_004f6aa0();
      FUN_004f6ab0(*(undefined4 *)(param_1 + 0x8c),DAT_0091757c,0x41000000,0);
      fVar2 = (float10)FUN_00822d80(*(undefined4 *)(param_1 + 0x88));
      FUN_0045c0f0((float)fVar2 + 5.0);
    }
  }
  if (*(char *)(param_1 + 0x65) == '\0') {
    iVar1 = FUN_004f6b10();
    if (((iVar1 < 1) && (*(char *)(param_1 + 0x66) == '\x01')) && (*(int *)(param_1 + 0x94) == 1)) {
      *(undefined1 *)(param_1 + 0x65) = 1;
      FUN_004f6aa0();
      FUN_004f6ab0(*(undefined4 *)(param_1 + 0x8c),DAT_009175b0,0x41000000,0);
      fVar2 = (float10)FUN_00822d80(*(undefined4 *)(param_1 + 0x84));
      FUN_0045c110((float)fVar2 + 5.0);
    }
  }
  return;
}

