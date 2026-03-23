
void FUN_006fdef0(int param_1)

{
  undefined4 local_c;
  int local_8;
  
  while (param_1 != 0) {
    local_8 = FUN_006d6720(&param_1);
    if (local_8 == 0) {
      local_8 = FUN_006d6730(&param_1);
      FUN_006d6670(&param_1);
      FUN_00700ac0(&param_1);
    }
    else {
      local_c = FUN_006d6730(&local_8);
      FUN_006d76e0(&param_1,&local_c);
      FUN_006d7700(&local_8,&param_1);
    }
    param_1 = local_8;
  }
  return;
}

