
void FUN_007e1420(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  format_string_parser<wchar_t> *pfVar5;
  undefined4 extraout_var;
  undefined4 uVar6;
  uint uVar7;
  undefined1 local_84 [44];
  format_string_parser<wchar_t> local_58 [36];
  undefined1 local_34 [32];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008639f8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar7 = 0;
  local_14 = uVar1;
  uVar2 = FUN_007e1640(param_2,param_3,param_4);
  uVar6 = extraout_var;
  FUN_007de5c0(uVar2);
  local_8 = 0;
  puVar4 = local_34;
  uVar2 = param_4;
  uVar3 = FUN_007e3090(param_2,puVar4,param_4,uVar1,uVar6);
  FUN_007e1800(local_58,uVar3,puVar4,uVar2);
  local_8._0_1_ = 1;
  pfVar5 = local_58;
  uVar2 = FUN_007e3040(param_2,pfVar5,param_4);
  FUN_007e1840(local_84,uVar2,pfVar5,param_4);
  local_8._0_1_ = 2;
  FUN_007ddd70(local_84);
  local_8._0_1_ = 1;
  ~input_processor<>(uVar1,uVar6,uVar7 | 1);
  local_8 = (uint)local_8._1_3_ << 8;
  __crt_stdio_input::format_string_parser<wchar_t>::~format_string_parser<wchar_t>(local_58);
  local_8 = 0xffffffff;
  FUN_007dba50();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

