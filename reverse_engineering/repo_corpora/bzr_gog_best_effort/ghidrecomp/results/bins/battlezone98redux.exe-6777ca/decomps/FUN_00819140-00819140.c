
int __thiscall FUN_00819140(int param_1,uint param_2,char param_3)

{
  if (8 < param_2) {
    FUN_008193e0();
  }
  if (param_3 == '\0') {
    *(uint *)(param_1 + (param_2 >> 5) * 4) =
         ~(1 << (sbyte)((ulonglong)param_2 % 0x20)) & *(uint *)(param_1 + (param_2 >> 5) * 4);
  }
  else {
    *(uint *)(param_1 + (param_2 >> 5) * 4) =
         1 << (sbyte)((ulonglong)param_2 % 0x20) | *(uint *)(param_1 + (param_2 >> 5) * 4);
  }
  return param_1;
}

