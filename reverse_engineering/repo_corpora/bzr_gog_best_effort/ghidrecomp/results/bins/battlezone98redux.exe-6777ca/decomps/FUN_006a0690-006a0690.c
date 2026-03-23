
uint FUN_006a0690(int *param_1,uint param_2)

{
  uint local_8;
  
  if ((0x8b < *param_1) || (*param_1 < 0)) {
    *param_1 = 0;
  }
  if ((int)param_2 < 1) {
    local_8 = 0;
  }
  else {
    local_8 = *(uint *)(&DAT_008ed7c8 + *param_1 * 4) % param_2;
  }
  *param_1 = *param_1 + 1;
  return local_8;
}

