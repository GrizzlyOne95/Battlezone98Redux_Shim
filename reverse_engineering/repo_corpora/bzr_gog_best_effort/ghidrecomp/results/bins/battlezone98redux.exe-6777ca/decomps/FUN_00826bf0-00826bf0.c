
uint * FUN_00826bf0(uint *param_1,int param_2,uint param_3)

{
  int local_c;
  uint *local_8;
  
  local_8 = param_1;
  local_c = param_2 >> 2;
  while( true ) {
    if (local_c < 1) break;
    *local_8 = *local_8 ^ param_3;
    local_8 = local_8 + 1;
    local_c = local_c + -1;
  }
  return param_1;
}

