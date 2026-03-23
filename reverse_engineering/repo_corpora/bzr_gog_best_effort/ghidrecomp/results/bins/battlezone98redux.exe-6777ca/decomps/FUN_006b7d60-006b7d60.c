
void FUN_006b7d60(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  _String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *this;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined1 local_154 [4];
  undefined1 local_150 [4];
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined1 local_114 [88];
  undefined1 local_bc [96];
  undefined1 local_5c [48];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850dc1;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006da060(&local_118,param_1,param_2,&DAT_008730fc,&DAT_008730fd,local_14);
  cVar1 = FID_conflict_operator__(&param_2);
  if (cVar1 != '\0') {
    basic_string<>("Invalid header line");
    local_8 = 0;
    local_128 = basic_string<>();
    local_8._0_1_ = 1;
    local_124 = local_128;
    local_12c = basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    local_120 = local_12c;
    FUN_006b7140(local_2c,400,local_12c,local_124);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_114,(ThrowInfo *)&DAT_008d838c);
  }
  puVar3 = local_154;
  uVar4 = param_2;
  this = (_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *)
         FID_conflict_operator_(local_150,2);
  puVar2 = (undefined4 *)
           std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_>::
           operator-(this,(int)puVar3);
  local_13c = FUN_006da0a0(*puVar2,uVar4);
  local_8 = 3;
  local_134 = local_13c;
  local_144 = FUN_006b7250(local_bc,local_13c);
  local_8._0_1_ = 4;
  local_11c = local_144;
  local_14c = FUN_006da0a0(param_1,local_118);
  local_8._0_1_ = 5;
  local_148 = local_14c;
  local_140 = FUN_006b7250(local_5c,local_14c);
  local_8._0_1_ = 6;
  local_138 = local_140;
  FUN_006b7570(local_140,local_11c);
  local_8._0_1_ = 5;
  ~basic_string<>();
  local_8._0_1_ = 4;
  ~basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

