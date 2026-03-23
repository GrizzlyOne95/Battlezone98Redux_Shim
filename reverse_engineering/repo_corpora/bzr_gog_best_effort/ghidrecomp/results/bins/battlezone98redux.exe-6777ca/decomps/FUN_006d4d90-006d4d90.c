
void __thiscall
FUN_006d4d90(undefined4 *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3,
            undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined4 *local_34;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085343e;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  local_34 = param_1;
  local_14 = uVar1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 8),param_2);
  local_8._0_1_ = 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (local_34 + 0xe),param_3);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_006cb470(uVar1);
  *local_34 = param_4;
  local_34[1] = 0;
  FUN_006d57b0(local_38);
  uVar2 = FUN_006b3f60();
  local_34[2] = uVar2;
  FUN_006d57b0(local_3c);
  uVar2 = FUN_006b3f70();
  local_34[3] = uVar2;
  local_34[4] = 0;
  local_34[5] = 0;
  local_34[6] = 0;
  local_34[7] = 0;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

