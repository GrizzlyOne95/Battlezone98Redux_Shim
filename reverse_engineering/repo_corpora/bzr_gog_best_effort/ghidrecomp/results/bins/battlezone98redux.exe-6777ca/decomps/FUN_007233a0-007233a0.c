
undefined4 FUN_007233a0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uStack_150;
  undefined1 auStack_140 [108];
  undefined1 local_d4 [84];
  undefined4 local_80;
  undefined4 uStack_78;
  undefined4 local_5c;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_30;
  uint local_2c;
  uint local_24;
  undefined4 local_20;
  char local_1a;
  char local_19;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00858d91;
  local_10 = ExceptionList;
  uStack_150 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_150;
  ExceptionList = &local_10;
  local_2c = 0;
  local_8 = 0;
  local_80 = FUN_004bb540(local_d4);
  local_8._0_1_ = 1;
  local_5c = local_80;
  local_24 = FUN_00726690(local_80);
  local_8._0_1_ = 0;
  FUN_004bb3b0();
  local_20 = *(undefined4 *)(local_18 + 0x10);
  cVar1 = FID_conflict_operator__(&stack0x00000018);
  if (cVar1 != '\0') {
    uStack_78 = FUN_004bb540(auStack_140);
    local_8._0_1_ = 0x12;
    uStack_30 = uStack_78;
    FID_conflict_operator_(param_1,local_24);
    local_2c = local_2c | 1;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004bb3b0();
    local_8 = 0xffffffff;
    FUN_004bb3d0();
    ExceptionList = local_10;
    return param_1;
  }
  if (local_24 <= *(uint *)(local_18 + 0x10) >> 1) {
    local_8 = CONCAT31(local_8._1_3_,2);
    while( true ) {
      local_1a = FID_conflict_operator__(&stack0x00000018);
      if (local_1a == '\0') break;
      local_3c = get();
      FUN_00726350(local_3c);
      std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
      operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                  *)&stack0x00000014);
    }
    uVar2 = FUN_007234b0();
    return uVar2;
  }
  local_8 = CONCAT31(local_8._1_3_,10);
  while( true ) {
    local_19 = FID_conflict_operator__(&stack0x00000018);
    if (local_19 == '\0') break;
    local_40 = get();
    FUN_00726500(local_40);
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &stack0x00000014);
  }
  uVar2 = FUN_007236a6();
  return uVar2;
}

