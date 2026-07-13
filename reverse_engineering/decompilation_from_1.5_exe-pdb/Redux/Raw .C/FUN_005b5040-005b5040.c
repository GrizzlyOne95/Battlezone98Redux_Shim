
uint __thiscall FUN_005b5040(int param_1,byte param_2)

{
  return *(uint *)(param_1 + 400) >> (param_2 & 0x1f) & 1;
}

