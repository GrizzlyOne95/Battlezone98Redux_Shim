
void __thiscall FUN_007cb380(int param_1,undefined1 param_2)

{
  undefined1 auStack_18 [8];
  undefined4 local_10;
  undefined1 *local_c;
  int local_8;
  
  *(undefined1 *)(param_1 + 0x158) = param_2;
  if ((*(char *)(param_1 + 0x158) == '\0') && ((*(uint *)(param_1 + 0x14) & 0x10) != 0)) {
    local_c = auStack_18;
    local_8 = param_1;
    local_10 = FUN_004498d0(param_1 + 0x114);
    FUN_007d2b70();
    *(undefined1 *)(local_8 + 0x148) = 0;
  }
  return;
}

