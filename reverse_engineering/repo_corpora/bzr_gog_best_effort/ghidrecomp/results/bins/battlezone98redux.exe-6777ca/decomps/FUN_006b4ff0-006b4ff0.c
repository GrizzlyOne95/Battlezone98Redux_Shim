
void __thiscall
FUN_006b4ff0(exception *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_50;
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085095b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  std::exception::exception(param_1);
  local_8 = 0;
  *(undefined ***)param_1 = websocketpp::exception::vftable;
  cVar1 = FUN_0041f890(uVar2);
  bVar3 = cVar1 == '\0';
  if (bVar3) {
    local_50 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (local_2c,param_2);
    local_8 = 2;
  }
  else {
    local_50 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_006ab780(local_44);
    local_8 = CONCAT31(local_8._1_3_,1);
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0xc),local_50);
  local_8 = 1;
  if (bVar3) {
    ~basic_string<>();
  }
  local_8 = 0;
  if (!bVar3) {
    ~basic_string<>();
  }
  *(undefined4 *)(param_1 + 0x24) = param_3;
  *(undefined4 *)(param_1 + 0x28) = param_4;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

