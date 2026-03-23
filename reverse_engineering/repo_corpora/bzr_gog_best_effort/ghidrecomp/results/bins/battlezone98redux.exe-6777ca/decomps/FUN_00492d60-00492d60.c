
int FUN_00492d60(int param_1,int param_2)

{
  return *(int *)(&DAT_02cc5108 +
                 (((int)(param_1 + 0x1800U) >> 8 & 0x7fU) +
                 ((int)(param_2 + 0x1800U) >> 8 & 0x7fU) * 0x80) * 4) +
         ((param_1 + 0x1800U & 0xff) + (param_2 + 0x1800U & 0xff) * 0x100) * 2;
}

