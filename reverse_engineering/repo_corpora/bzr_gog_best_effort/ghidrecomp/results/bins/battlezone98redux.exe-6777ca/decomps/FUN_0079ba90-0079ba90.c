
void FUN_0079ba90(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint in_stack_00000024;
  uint in_stack_00000028;
  char in_stack_0000002c;
  char in_stack_00000030;
  undefined4 uStack_19c;
  char *pcStack_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined1 *puStack_18c;
  basic_ostream<char,struct_std::char_traits<char>_> local_180 [188];
  undefined4 local_c4;
  undefined1 *local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  uint local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  int local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  uint *local_90;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085f879;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_a8 = FUN_0056f900();
  if ((local_a8 != 0) && (iVar1 = FUN_007a4220(), iVar1 != 0)) {
    local_b4 = *param_1;
    local_90 = param_1;
    if (in_stack_0000002c == '\0') {
      if (in_stack_00000028 < *param_1) {
        *param_1 = in_stack_00000028;
      }
      if (*param_1 < in_stack_00000024) {
        *param_1 = in_stack_00000024;
      }
    }
    else if (in_stack_00000030 == '\0') {
      *param_1 = *param_1 - 1;
      if ((in_stack_00000028 < *param_1) || (*param_1 < in_stack_00000024)) {
        *param_1 = in_stack_00000028;
      }
    }
    else {
      *param_1 = *param_1 + 1;
      if ((in_stack_00000028 < *param_1) || (*param_1 < in_stack_00000024)) {
        *param_1 = in_stack_00000024;
      }
    }
    puStack_18c = (undefined1 *)0x2;
    uStack_190 = 0x79bbdc;
    FUN_006ca050();
    local_8._0_1_ = 1;
    puStack_18c = (undefined1 *)0x79bbf5;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_180,*local_90);
    puStack_18c = (undefined1 *)0x0;
    uStack_190 = 0;
    uStack_194 = 0x79bc06;
    FUN_00426b10();
    local_8._0_1_ = 2;
    puStack_18c = &DAT_02cf2000;
    uStack_190 = 0x79bc19;
    FUN_00426a60();
    local_8._0_1_ = 3;
    puStack_18c = (undefined1 *)0x79bc2a;
    FUN_00426af0();
    puStack_18c = (undefined1 *)0x79bc36;
    local_a4 = FUN_00417fd0();
    local_8._0_1_ = 4;
    local_9c = local_a4;
    FUN_0041f870();
    puStack_18c = (undefined1 *)0x79bc63;
    FUN_00426c30();
    local_8._0_1_ = 3;
    ~basic_string<>();
    puStack_18c = (undefined1 *)0x79bc81;
    local_bc = GetPolicy();
    local_8._0_1_ = 5;
    puStack_18c = (undefined1 *)0x0;
    uStack_190 = 0x79bca6;
    local_ac = local_bc;
    uStack_190 = FUN_0041f870();
    uStack_194 = 0x79bcaf;
    uStack_194 = FUN_0041f870();
    pcStack_198 = "multi";
    uStack_19c = 0x79bcc0;
    FUN_00421f90();
    local_8._0_1_ = 3;
    ~basic_string<>();
    puStack_18c = (undefined1 *)0x79bcdb;
    local_b8 = FUN_00417fd0();
    local_8._0_1_ = 6;
    puStack_18c = (undefined1 *)0x79bcfe;
    local_a0 = local_b8;
    puStack_18c = (undefined1 *)FUN_0041f870();
    uStack_190 = 0x79bd0a;
    FUN_00426c90();
    local_8._0_1_ = 3;
    ~basic_string<>();
    puStack_18c = (undefined1 *)0x79bd25;
    local_b0 = GetPolicy();
    local_8._0_1_ = 7;
    local_98 = local_b0;
    uVar2 = FUN_0041f870();
    local_c0 = (undefined1 *)&uStack_19c;
    local_c4 = basic_string<>(uVar2);
    FUN_007c44a0();
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
    if (local_b4 != *param_1) {
      FUN_0073d020();
    }
    local_8._0_1_ = 2;
    FUN_004180b0();
    local_8._0_1_ = 1;
    FUN_00426bc0();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006b3a50();
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

