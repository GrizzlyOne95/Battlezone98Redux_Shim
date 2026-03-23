
void FUN_004e3220(uint param_1,uint *param_2,uint *param_3)

{
  *param_3 = param_1 & 0xffff;
  *param_2 = param_1 >> 0x10;
  return;
}

