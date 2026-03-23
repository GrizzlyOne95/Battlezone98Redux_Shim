
void FUN_0071ffb0(int *param_1,int *param_2)

{
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  if (*param_1 != *param_2) {
    local_8 = FUN_006d6700(param_1);
    local_14 = FUN_006d6700(param_2);
    FUN_006d76c0(param_1,&local_14);
    FUN_006d76c0(param_2,&local_8);
    local_8 = FUN_006d6720(param_1);
    local_18 = FUN_006d6720(param_2);
    FUN_006d76e0(param_1,&local_18);
    FUN_006d76e0(param_2,&local_8);
    local_8 = FUN_006d6730(param_1);
    local_1c = FUN_006d6730(param_2);
    FUN_006d7700(param_1,&local_1c);
    FUN_006d7700(param_2,&local_8);
    local_c = FUN_006d6700(param_1);
    if (local_c == 0) {
      FUN_006d76e0(param_1,param_1);
      FUN_006d7700(param_1,param_1);
    }
    else {
      FUN_006d76c0(&local_c,param_1);
    }
    local_10 = FUN_006d6700(param_2);
    if (local_10 == 0) {
      FUN_006d76e0(param_2,param_2);
      FUN_006d7700(param_2,param_2);
    }
    else {
      FUN_006d76c0(&local_10,param_2);
    }
  }
  return;
}

