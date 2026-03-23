
void __thiscall
FUN_006b59a0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *in_stack_0000001c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *in_stack_00000020;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_58;
  undefined4 local_54;
  undefined2 local_4e;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00850aff;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_14 = uVar2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (param_1,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )&stack0x00000004);
  local_8._0_1_ = 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (param_1 + 0x18,in_stack_0000001c);
  local_8._0_1_ = 2;
  cVar1 = FUN_0041f890(uVar2);
  bVar3 = cVar1 == '\0';
  if (bVar3) {
    local_54 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (local_2c,in_stack_00000020);
  }
  else {
    local_54 = basic_string<>(&DAT_008922f8);
    local_8._0_1_ = 3;
  }
  basic_string<>(local_54);
  local_8 = 4;
  if (bVar3) {
    ~basic_string<>();
  }
  local_8 = CONCAT31(local_8._1_3_,5);
  if (!bVar3) {
    ~basic_string<>();
  }
  cVar1 = FUN_00427270(&stack0x00000004,&PTR_LAB_00896ca8);
  if (cVar1 == '\0') {
    cVar1 = FUN_00427270(&stack0x00000004,"https");
    if (cVar1 != '\0') goto LAB_006b5ad7;
    local_4e = 0x50;
  }
  else {
LAB_006b5ad7:
    local_4e = 0x1bb;
  }
  *(undefined2 *)(param_1 + 0x48) = local_4e;
  cVar1 = FUN_00427270(&stack0x00000004,&PTR_LAB_00896ca8);
  if (cVar1 == '\0') {
    cVar1 = FUN_00427270(&stack0x00000004,"https");
    if (cVar1 == '\0') {
      local_58 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
      goto LAB_006b5b2b;
    }
  }
  local_58 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x1;
LAB_006b5b2b:
  param_1[0x4a] = local_58;
  param_1[0x4b] = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x1;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

