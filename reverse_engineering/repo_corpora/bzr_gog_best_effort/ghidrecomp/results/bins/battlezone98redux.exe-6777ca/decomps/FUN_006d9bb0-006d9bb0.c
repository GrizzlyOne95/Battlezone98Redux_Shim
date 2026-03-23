
void FUN_006d9bb0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  undefined1 local_dc [4];
  undefined1 local_d8 [4];
  undefined1 local_d4 [4];
  undefined1 local_d0 [4];
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined1 local_b0 [8];
  undefined4 local_a8;
  CTraceSnapshot local_a4 [32];
  CTraceSnapshot local_84 [32];
  undefined1 local_64 [28];
  undefined1 local_48 [24];
  undefined4 local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008537b6;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00423890(local_14);
  cVar1 = FID_conflict_operator__(&param_3);
  if (cVar1 == '\0') {
    local_a8 = param_2;
    FUN_006e3330();
    local_8 = 0;
    while( true ) {
      cVar1 = FID_conflict_operator__(&param_3);
      if (cVar1 == '\0') break;
      basic_string<>();
      local_8._0_1_ = 1;
      FUN_006ca5f0();
      local_8._0_1_ = 2;
      puVar2 = (undefined4 *)FUN_006d9a90(local_d0,local_a8,param_3);
      local_a8 = *puVar2;
      cVar1 = FID_conflict_operator__(&param_3);
      if (cVar1 != '\0') {
        local_8._0_1_ = 1;
        FUN_006b7450();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        break;
      }
      local_cc = FUN_006e8150(local_64,local_a8,param_3);
      local_8._0_1_ = 3;
      local_bc = local_cc;
      FUN_006e3390(local_cc);
      local_8._0_1_ = 2;
      FUN_00430320();
      cVar1 = FUN_0041f890();
      if (cVar1 != '\0') {
        *param_1 = param_2;
        local_8._0_1_ = 1;
        FUN_006b7450();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_00430320();
        goto LAB_006da016;
      }
      FID_conflict_operator_(local_48);
      local_a8 = local_30;
      puVar2 = (undefined4 *)FUN_006d9a90(local_d8,local_30,param_3);
      local_a8 = *puVar2;
      cVar1 = FID_conflict_operator__(&param_3);
      if (cVar1 != '\0') {
        local_c8 = FUN_006e8200(local_84,local_2c,local_b0);
        local_8._0_1_ = 4;
        local_c0 = local_c8;
        FUN_006e0e50(local_c8);
        local_8._0_1_ = 2;
        CTraceSnapshot::~CTraceSnapshot(local_84);
        local_8._0_1_ = 1;
        FUN_006b7450();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        break;
      }
      pcVar3 = (char *)get();
      if (*pcVar3 == ';') {
        FUN_00423890();
        std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
        operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                    *)&local_a8);
        puVar2 = (undefined4 *)FUN_006e8240(local_d4,local_a8,param_3,local_b0);
        local_b4 = *puVar2;
        cVar1 = FID_conflict_operator__(&local_a8);
        if (cVar1 != '\0') {
          *param_1 = param_2;
          local_8._0_1_ = 1;
          FUN_006b7450();
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          local_8 = 0xffffffff;
          FUN_00430320();
          goto LAB_006da016;
        }
        local_a8 = local_b4;
      }
      local_c4 = FUN_006e8200(local_a4,local_2c,local_b0);
      local_8._0_1_ = 5;
      local_b8 = local_c4;
      FUN_006e0e50(local_c4);
      local_8._0_1_ = 2;
      CTraceSnapshot::~CTraceSnapshot(local_a4);
      puVar2 = (undefined4 *)FUN_006d9a90(local_dc,local_a8,param_3);
      local_a8 = *puVar2;
      cVar1 = FID_conflict_operator__(&param_3);
      if (cVar1 != '\0') {
        local_8._0_1_ = 1;
        FUN_006b7450();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        break;
      }
      pcVar3 = (char *)get();
      if (*pcVar3 != ',') {
        local_8._0_1_ = 1;
        FUN_006b7450();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        break;
      }
      std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
      operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                  *)&local_a8);
      cVar1 = FID_conflict_operator__(&param_3);
      if (cVar1 != '\0') {
        *param_1 = param_2;
        local_8._0_1_ = 1;
        FUN_006b7450();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_00430320();
        goto LAB_006da016;
      }
      local_8._0_1_ = 1;
      FUN_006b7450();
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
    }
    *param_1 = local_a8;
    local_8 = 0xffffffff;
    FUN_00430320();
  }
  else {
    *param_1 = param_2;
  }
LAB_006da016:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

