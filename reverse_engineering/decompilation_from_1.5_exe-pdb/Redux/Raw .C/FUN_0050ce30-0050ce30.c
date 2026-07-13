
int FUN_0050ce30(int param_1,int param_2)

{
  return (uint)(byte)(&DAT_02cd5120)
                     [((int)(param_1 + 0x1800U) >> 8 & 0x7fU) +
                      ((int)(param_2 + 0x1800U) >> 8 & 0x7fU) * 0x80] * 0x10000 + DAT_009454c4 +
         (param_1 + 0x1800U & 0xff) + (param_2 + 0x1800U & 0xff) * 0x100;
}

