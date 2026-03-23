
void __thiscall FUN_007cccd0(int param_1,char param_2)

{
  if (param_2 == '\0') {
    *(uint *)(param_1 + 0x100) = *(uint *)(param_1 + 0x100) & 0xffffff;
  }
  else {
    *(uint *)(param_1 + 0x100) = *(uint *)(param_1 + 0x100) | 0xff000000;
  }
  FUN_007ccfc0();
  return;
}

