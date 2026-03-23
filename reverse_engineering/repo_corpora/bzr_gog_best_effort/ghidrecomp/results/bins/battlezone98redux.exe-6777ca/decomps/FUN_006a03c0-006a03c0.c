
void FUN_006a03c0(short *param_1)

{
  short *local_8;
  
  local_8 = param_1 + 1;
  if (*param_1 != 0) {
    while (*local_8 != 0) {
      if (*param_1 == *local_8) {
        FUN_006a0430(local_8);
      }
      else {
        local_8 = local_8 + 1;
      }
    }
    FUN_006a03c0(param_1 + 1);
  }
  return;
}

