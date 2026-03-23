
uint __thiscall FUN_004625d0(int param_1,byte param_2)

{
  return *(uint *)(param_1 + 0x18c) >> (param_2 & 0x1f) & 1;
}

