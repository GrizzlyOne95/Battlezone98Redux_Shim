
undefined1 FUN_0046ae20(int param_1,int param_2)

{
  int iVar1;
  undefined1 local_14;
  
  param_2 = param_2 - DAT_02cd9984;
  if ((param_2 < 0) || (DAT_02ce99c4 - DAT_02cd9984 <= param_2)) {
    local_14 = 1;
  }
  else {
    param_1 = param_1 - DAT_02ce99c0;
    if ((param_1 < 0) || (DAT_02ce99a0 - DAT_02ce99c0 <= param_1)) {
      local_14 = 1;
    }
    else {
      iVar1 = FUN_00591670(*(undefined1 *)
                            (DAT_0260d178 + (DAT_02ce99a0 - DAT_02ce99c0) * param_2 + param_1));
      if ((iVar1 == 6) || (iVar1 == 5)) {
        local_14 = 1;
      }
      else {
        local_14 = 0;
      }
    }
  }
  return local_14;
}

