
void FUN_006678e0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1,undefined4 param_2,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_0041f890(local_14);
  if (cVar1 == '\0') {
    uVar2 = FUN_0041f870();
    cVar1 = FUN_00667860(uVar2);
    if (cVar1 == '\0') {
      uVar2 = FUN_0066e720(local_2c,param_2,0x2f);
      local_8 = 0;
      FUN_00426a20(param_1,uVar2,param_3);
      local_8 = 0xffffffff;
      ~basic_string<>();
      goto LAB_006679a1;
    }
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1,param_3);
LAB_006679a1:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

