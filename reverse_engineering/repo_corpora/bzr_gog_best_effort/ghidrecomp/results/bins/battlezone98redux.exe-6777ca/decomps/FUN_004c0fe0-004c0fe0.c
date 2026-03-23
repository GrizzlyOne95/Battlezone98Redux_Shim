
int FUN_004c0fe0(int param_1,int param_2)

{
  param_1 = param_1 + 0x1800;
  param_2 = param_2 + 0x1800;
  return *(int *)(&DAT_02cd99a0 + ((param_1 >> 8 & 0x7fU) + (param_2 >> 8 & 0x7fU) * 0x80) * 4) +
         (((int)(param_1 + (param_1 >> 0x1f & 3U)) >> 2 & 0x3fU) +
         ((int)(param_2 + (param_2 >> 0x1f & 3U)) >> 2 & 0x3fU) * 0x40) * 2;
}

