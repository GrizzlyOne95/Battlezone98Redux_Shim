
void FUN_004d9ae0(int param_1,int param_2)

{
  *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0xfff0ffff | param_2 << 0x10;
  return;
}

