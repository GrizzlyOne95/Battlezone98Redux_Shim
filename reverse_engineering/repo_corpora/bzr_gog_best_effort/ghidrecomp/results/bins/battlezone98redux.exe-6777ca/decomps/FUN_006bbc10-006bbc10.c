
void FUN_006bbc10(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  iterator *this;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined1 local_4c [16];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  uint local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00848fd8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = 0;
  basic_string<>(local_14);
  local_8 = 0;
  puVar2 = (undefined4 *)FUN_006ab750();
  uVar5 = puVar2[1];
  *param_3 = *puVar2;
  param_3[1] = uVar5;
  uVar3 = FUN_004170c0();
  if (2 < uVar3) {
    puVar2 = (undefined4 *)FUN_004fee40(local_3c);
    uVar5 = *puVar2;
    puVar4 = local_38;
    this = (iterator *)FID_conflict_begin(local_34);
    puVar2 = (undefined4 *)
             std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             iterator::operator+(this,(int)puVar4);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    assign<class_std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>
              (local_2c,*puVar2,uVar5);
  }
  cVar1 = FUN_006bb9a0(local_2c);
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)make_error_code(local_4c,0xd);
    uVar5 = puVar2[1];
    *param_3 = *puVar2;
    param_3[1] = uVar5;
  }
  basic_string<>(local_2c);
  local_30 = local_30 | 1;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

