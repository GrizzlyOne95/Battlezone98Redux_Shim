
void __thiscall FUN_005a38a0(int param_1,byte param_2)

{
  *(uint *)(param_1 + 0x194) = ~(1 << (param_2 & 0x1f)) & *(uint *)(param_1 + 0x194);
  return;
}

