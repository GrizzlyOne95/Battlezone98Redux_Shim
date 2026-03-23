
undefined4 FUN_006b5e90(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  ushort uVar3;
  undefined1 auStack_bc [160];
  int local_1c;
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850b3b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xcc) {
    local_14 = (undefined1 *)0x0;
  }
  else {
    local_14 = auStack_bc;
  }
  uVar3 = *(ushort *)(local_1c + 0x48);
  uVar2 = FUN_00574730(local_14,local_1c + 0x18,&DAT_00896ce8,uVar3,uVar1);
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,uVar3);
  GetPolicy(param_1);
  local_18 = local_18 | 1;
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  return param_1;
}

