
void __thiscall FUN_007ccd20(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x100) = *(uint *)(param_1 + 0x100) & 0xff000000 | param_2;
  FUN_007ccfc0();
  return;
}

