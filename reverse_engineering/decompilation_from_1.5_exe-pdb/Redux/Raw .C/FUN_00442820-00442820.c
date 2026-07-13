
void FUN_00442820(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0xffff0fff | param_2 & 0xf000;
  return;
}

