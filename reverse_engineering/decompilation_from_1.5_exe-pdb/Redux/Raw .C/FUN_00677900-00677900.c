
void FUN_00677900(char *param_1,char *param_2)

{
  char *local_c;
  char *local_8;
  
  if (param_1 != param_2) {
    local_c = param_2;
    for (local_8 = param_1; local_8 != param_1 + 0x10; local_8 = local_8 + 1) {
      std::iter_swap<char*,char*>(local_8,local_c);
      local_c = local_c + 1;
    }
  }
  return;
}

