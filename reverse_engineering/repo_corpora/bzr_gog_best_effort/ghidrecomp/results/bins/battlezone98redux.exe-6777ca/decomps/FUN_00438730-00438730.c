
undefined1 FUN_00438730(undefined4 param_1)

{
  char cVar1;
  int local_34;
  undefined1 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int *local_24;
  size_t local_20;
  uint local_1c;
  int local_18;
  int *local_14;
  int *local_10;
  int local_c;
  char local_5;
  
  local_5 = 1;
  cVar1 = FUN_004ce910(param_1,&local_34,4);
  local_5 = cVar1 != '\0';
  local_1c = (uint)(byte)local_5;
  for (local_c = 0; local_c < local_34; local_c = local_c + 1) {
    local_20 = 8;
    local_14 = operator_new(8);
    if (local_14 == (int *)0x0) {
      local_24 = (int *)0x0;
    }
    else {
      memset(local_14,0,local_20);
      local_24 = local_14;
    }
    local_10 = local_24;
    if ((local_5 == '\0') || (cVar1 = FUN_004ce910(param_1,local_24 + 1,4), cVar1 == '\0')) {
      local_28 = 0;
    }
    else {
      local_28 = 1;
    }
    local_5 = (char)local_28;
    if (((char)local_28 == '\0') ||
       (cVar1 = FUN_004ce400(param_1,&DAT_0260c258 + local_c * 0xe,0xe), cVar1 == '\0')) {
      local_2c = 0;
    }
    else {
      local_2c = 1;
    }
    local_5 = (char)local_2c;
    *local_10 = (int)(&DAT_0260c258 + local_c * 0xe);
    FUN_00438be0(&local_10);
    *(int *)(local_18 + 0x30) = local_10[1] + 1;
  }
  if ((local_5 == '\0') || (cVar1 = FUN_004ce400(param_1,local_18 + 0x40,0x10), cVar1 == '\0')) {
    local_30 = 0;
  }
  else {
    local_30 = 1;
  }
  return local_30;
}

