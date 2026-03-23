
uint FUN_0073bd40(uint *param_1,uint *param_2,uint param_3)

{
  byte bVar1;
  uint local_8;
  
  bVar1 = (&DAT_008735a8)[param_3];
  if (*param_1 == 0) {
    local_8 = 0xff >> (bVar1 & 0x1f) & param_3;
  }
  else {
    local_8 = param_3 & 0x3f | *param_2 << 6;
  }
  *param_2 = local_8;
  *param_1 = (uint)(byte)(&DAT_008736a8)[(uint)bVar1 + *param_1 * 0x10];
  return *param_1;
}

