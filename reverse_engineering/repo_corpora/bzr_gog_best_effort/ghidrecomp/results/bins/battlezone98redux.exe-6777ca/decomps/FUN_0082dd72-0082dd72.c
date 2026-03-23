
void FUN_0082dd72(int param_1)

{
  *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
  *(undefined1 **)(param_1 + 8) = &DAT_008a1ad8;
  *(undefined1 **)(param_1 + 4) = &DAT_008a1ad8;
  *(char **)(param_1 + 0x10) = "=(tail call)";
  *(undefined **)(param_1 + 0xc) = &DAT_0086ec28;
  FUN_0082e741(param_1 + 0x24,"=(tail call)",0x3c);
  *(undefined4 *)(param_1 + 0x18) = 0;
  return;
}

