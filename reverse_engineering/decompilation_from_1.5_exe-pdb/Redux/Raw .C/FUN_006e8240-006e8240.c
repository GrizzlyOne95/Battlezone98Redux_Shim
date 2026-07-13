
void FUN_006e8240(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  undefined1 *puVar4;
  undefined1 local_cc [4];
  undefined1 local_c8 [4];
  undefined1 local_c4 [4];
  undefined1 local_c0 [4];
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  char local_a1;
  undefined4 local_a0;
  undefined1 local_9c [28];
  undefined1 local_80 [28];
  undefined1 local_64 [28];
  undefined1 local_48 [24];
  undefined1 local_30 [24];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085477b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00423890(local_14);
  local_a1 = '\x01';
  cVar1 = FID_conflict_operator__(&param_3);
  if (cVar1 == '\0') {
    local_a0 = param_2;
    FUN_006e3330();
    local_8 = 0;
    while( true ) {
      cVar1 = FID_conflict_operator__(&param_3);
      if (cVar1 == '\0') break;
      basic_string<>();
      local_8._0_1_ = 1;
      puVar2 = (undefined4 *)FUN_006d9a90(local_c0,local_a0,param_3);
      local_a0 = *puVar2;
      cVar1 = FID_conflict_operator__(&param_3);
      if (cVar1 != '\0') {
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        break;
      }
      if (local_a1 == '\0') {
        pcVar3 = (char *)get();
        if (*pcVar3 != ';') {
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          break;
        }
        std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
        operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                    *)&local_a0);
      }
      else {
        local_a1 = '\0';
      }
      puVar2 = (undefined4 *)FUN_006d9a90(local_c4,local_a0,param_3);
      local_a0 = *puVar2;
      local_b4 = FUN_006e8150(local_80,local_a0,param_3);
      local_8._0_1_ = 2;
      local_b0 = local_b4;
      FUN_006e3390(local_b4);
      local_8._0_1_ = 1;
      FUN_00430320();
      cVar1 = FUN_0041f890();
      if (cVar1 != '\0') {
        *param_1 = param_2;
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_00430320();
        goto LAB_006e8668;
      }
      FID_conflict_operator_(local_30);
      local_a0 = local_18;
      puVar2 = (undefined4 *)FUN_006d9a90(local_cc,local_18,param_3);
      local_a0 = *puVar2;
      cVar1 = FID_conflict_operator__(&param_3);
      if (cVar1 == '\0') {
        pcVar3 = (char *)get();
        if (*pcVar3 != '=') goto LAB_006e8472;
        std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
        operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                    *)&local_a0);
        puVar2 = (undefined4 *)FUN_006d9a90(local_c8,local_a0,param_3);
        local_a0 = *puVar2;
        cVar1 = FID_conflict_operator__(&param_3);
        if (cVar1 != '\0') {
          *param_1 = param_2;
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          local_8 = 0xffffffff;
          FUN_00430320();
          goto LAB_006e8668;
        }
        local_b8 = FUN_006f7c40(local_9c,local_a0,param_3);
        local_8._0_1_ = 3;
        local_ac = local_b8;
        FUN_006e3390(local_b8);
        local_8._0_1_ = 1;
        FUN_00430320();
        cVar1 = FID_conflict_operator__(&local_a0);
        if (cVar1 == '\0') {
          local_bc = FUN_006e8150(local_64,local_a0,param_3);
          local_8._0_1_ = 4;
          local_a8 = local_bc;
          FUN_006e3390(local_bc);
          local_8._0_1_ = 1;
          FUN_00430320();
          cVar1 = FUN_0041f890();
          if (cVar1 != '\0') {
            *param_1 = param_2;
            local_8 = (uint)local_8._1_3_ << 8;
            ~basic_string<>();
            local_8 = 0xffffffff;
            FUN_00430320();
            goto LAB_006e8668;
          }
          puVar4 = local_30;
          FUN_006ca810(local_48);
          FID_conflict_operator_(puVar4);
          local_a0 = local_18;
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
        }
        else {
          puVar4 = local_30;
          FUN_006ca810(local_48);
          FID_conflict_operator_(puVar4);
          local_a0 = local_18;
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
        }
      }
      else {
LAB_006e8472:
        FUN_006ca810(local_48);
        FUN_0041f830();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
      }
    }
    *param_1 = local_a0;
    local_8 = 0xffffffff;
    FUN_00430320();
  }
  else {
    *param_1 = param_2;
  }
LAB_006e8668:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

