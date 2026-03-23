
undefined1 FUN_00575890(undefined4 param_1,undefined4 param_2,undefined4 param_3,char param_4)

{
  int iVar1;
  undefined *local_c;
  undefined1 local_5;
  
  if (((DAT_00917f48 == 0) || (*(int *)(DAT_00917f48 + 8) == 5)) ||
     (*(int *)(DAT_00917f48 + 8) == 6)) {
    local_5 = 0;
  }
  else {
    iVar1 = FUN_007659f0();
    if (iVar1 == 0) {
      local_5 = 0;
    }
    else {
      if (param_4 == '\0') {
        local_c = &DAT_009c8fc8;
      }
      else {
        local_c = &DAT_009c8fc0;
      }
      local_5 = FUN_00759750(local_c,param_1,param_2,param_3);
    }
  }
  return local_5;
}

