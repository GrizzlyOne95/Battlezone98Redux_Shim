
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_006b5d60(int param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  ushort uVar3;
  undefined1 auStack_c0 [160];
  undefined1 *local_20;
  uint local_1c;
  int local_18;
  short local_12;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fe9b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c = 0;
  if (*(char *)(param_1 + 0x4a) == '\0') {
    local_12 = 0x50;
  }
  else {
    local_12 = 0x1bb;
  }
  local_18 = param_1;
  if (*(short *)(param_1 + 0x48) == local_12) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (param_2,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)(param_1 + 0x18));
  }
  else {
    FUN_00574400(3,1);
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0xd0) {
      local_20 = (undefined1 *)0x0;
    }
    else {
      local_20 = auStack_c0;
    }
    uVar3 = *(ushort *)(local_18 + 0x48);
    uVar2 = FUN_00574730(local_20,local_18 + 0x18,&DAT_00896ce8,uVar3,uVar1);
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,uVar3);
    GetPolicy(param_2);
    local_1c = local_1c | 1;
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  return param_2;
}

