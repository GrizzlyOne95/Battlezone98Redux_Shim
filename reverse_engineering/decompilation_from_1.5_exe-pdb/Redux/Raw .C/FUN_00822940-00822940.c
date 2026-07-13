
float10 FUN_00822940(uint param_1,float param_2)

{
  return (float10)(*(float *)(&DAT_00873ae0 + (param_1 & 0xf) * 4) * param_2);
}

