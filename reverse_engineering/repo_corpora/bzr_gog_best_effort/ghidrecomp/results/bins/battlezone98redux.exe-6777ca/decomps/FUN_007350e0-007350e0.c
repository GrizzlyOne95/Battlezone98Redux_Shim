
int FUN_007350e0(undefined4 param_1,int *param_2)

{
  int iVar1;
  int *in_stack_00000020;
  int *in_stack_00000024;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a2b8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_1c = *param_2;
  local_20 = FUN_006d6700(param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (local_20 == 0) {
    *in_stack_00000024 = 0;
    *in_stack_00000020 = 0;
  }
  else {
    local_18 = local_20;
    local_30 = FUN_00735910(&local_18);
    local_34 = 0;
    local_24 = local_30;
    local_1c = local_30;
    local_14 = local_30;
    FUN_006d76e0(&local_1c,&local_34);
    local_38 = 0;
    FUN_006d7700(&local_1c,&local_38);
    FUN_006d76c0(&local_1c,param_2);
    <>(&stack0x00000018,&local_1c);
    local_8 = 0;
    while( true ) {
      while( true ) {
        while ((iVar1 = FUN_006d6720(&local_18), iVar1 != 0 &&
               (iVar1 = FUN_006d6720(&local_14), iVar1 == 0))) {
          local_18 = FUN_006d6720(&local_18);
          local_28 = local_14;
          local_14 = FUN_00735910(&local_18);
          local_3c = 0;
          FUN_006d76e0(&local_14,&local_3c);
          local_40 = 0;
          FUN_006d7700(&local_14,&local_40);
          FUN_006d76c0(&local_14,&local_28);
          FUN_006d76e0(&local_28,&local_14);
          if (local_24 == local_1c) {
            local_30 = local_14;
          }
        }
        iVar1 = FUN_006d6730(&local_18);
        if ((iVar1 == 0) || (iVar1 = FUN_006d6730(&local_14), iVar1 != 0)) break;
        local_18 = FUN_006d6730(&local_18);
        local_2c = local_14;
        local_14 = FUN_00735910(&local_18);
        local_44 = 0;
        FUN_006d76e0(&local_14,&local_44);
        local_48 = 0;
        FUN_006d7700(&local_14,&local_48);
        FUN_006d76c0(&local_14,&local_2c);
        FUN_006d7700(&local_2c,&local_14);
        local_24 = local_14;
      }
      if (local_18 == local_20) break;
      local_18 = FUN_006d6700(&local_18);
      local_14 = FUN_006d6700(&local_14);
    }
    FUN_00703d50();
    *in_stack_00000020 = local_30;
    *in_stack_00000024 = local_24;
    local_8 = 0xffffffff;
    FUN_00735d60();
  }
  ExceptionList = local_10;
  return local_1c;
}

