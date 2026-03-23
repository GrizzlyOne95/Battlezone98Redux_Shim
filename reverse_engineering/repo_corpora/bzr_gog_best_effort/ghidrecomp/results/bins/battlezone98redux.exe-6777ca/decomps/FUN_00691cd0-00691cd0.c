
int FUN_00691cd0(undefined4 param_1,int param_2,int param_3)

{
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_8 = 0;
  do {
    local_18 = FUN_00690c40(param_1,local_8,&local_1c,&local_20);
    if (local_18 != 0) {
      local_10 = param_2 - local_1c;
      local_14 = param_3 - local_20;
      if ((((local_10 < 4) && (-8 < local_10)) && (local_14 < 4)) && (-8 < local_14)) {
        local_c = 1;
      }
    }
    local_8 = local_8 + 1;
  } while ((local_18 != 0) && (local_c == 0));
  return local_c;
}

