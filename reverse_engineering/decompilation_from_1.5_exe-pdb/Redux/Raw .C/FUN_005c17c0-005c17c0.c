
void __thiscall FUN_005c17c0(int param_1,byte param_2)

{
  *(uint *)(param_1 + 0x18c) = 1 << (param_2 & 0x1f) | *(uint *)(param_1 + 0x18c);
  *(uint *)(param_1 + 400) = 1 << (param_2 & 0x1f) | *(uint *)(param_1 + 400);
  return;
}

