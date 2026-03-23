
void __thiscall FUN_005e12b0(int param_1,byte param_2)

{
  *(uint *)(param_1 + 0x17c) = 1 << (param_2 & 0x1f) | *(uint *)(param_1 + 0x17c);
  return;
}

