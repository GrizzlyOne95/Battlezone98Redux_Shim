
void __thiscall FUN_007cc5c0(int param_1,char param_2)

{
  if (param_2 == '\0') {
    *(uint *)(param_1 + 0x91c) = *(uint *)(param_1 + 0x91c) & 0xffffff;
  }
  else {
    *(uint *)(param_1 + 0x91c) = *(uint *)(param_1 + 0x91c) | 0xff000000;
  }
  FUN_007cca20(*(undefined4 *)(param_1 + 0x91c));
  return;
}

