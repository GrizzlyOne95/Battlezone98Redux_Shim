
void FUN_00580ca0(char *param_1,int param_2,char *param_3)

{
  char *pcVar1;
  int iVar2;
  char *local_20;
  char *local_1c;
  char *local_18;
  int local_14;
  char *local_c;
  int local_8;
  
  param_2 = param_2 - (int)param_1;
  local_8 = (int)param_3 - (int)param_1;
  local_14 = param_2;
  while (local_14 != 0) {
    iVar2 = local_8 % local_14;
    local_8 = local_14;
    local_14 = iVar2;
  }
  if (local_8 < (int)param_3 - (int)param_1) {
    for (; 0 < local_8; local_8 = local_8 + -1) {
      pcVar1 = param_1 + local_8;
      if (pcVar1 + param_2 == param_3) {
        local_1c = param_1;
      }
      else {
        local_1c = pcVar1 + param_2;
      }
      local_c = local_1c;
      local_18 = pcVar1;
      do {
        std::iter_swap<char*,char*>(local_18,local_c);
        local_18 = local_c;
        if (param_2 < (int)param_3 - (int)local_c) {
          local_20 = local_c + param_2;
        }
        else {
          local_20 = param_1 + (param_2 - ((int)param_3 - (int)local_c));
        }
        local_c = local_20;
      } while (local_20 != pcVar1);
    }
  }
  return;
}

