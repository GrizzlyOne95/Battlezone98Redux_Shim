
undefined4 FUN_006b6030(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  ushort uVar3;
  undefined1 auStack_c8 [160];
  undefined1 *local_28;
  uint local_24;
  undefined1 *local_20;
  undefined1 *local_1c;
  short local_16;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850b6b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_24 = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xd8) {
    local_28 = (undefined1 *)0x0;
  }
  else {
    local_28 = auStack_c8;
  }
  uVar2 = FUN_00574730(local_28,local_14,&DAT_00896ce4,local_14 + 0x18,uVar1);
  uVar2 = FUN_004bc590(uVar2);
  FUN_00574730(uVar2);
  if (*(char *)(local_14 + 0x4a) == '\0') {
    local_16 = 0x50;
  }
  else {
    local_16 = 0x1bb;
  }
  if (*(short *)(local_14 + 0x48) != local_16) {
    if (&stack0x00000000 == (undefined1 *)0xd8) {
      local_1c = (undefined1 *)0x0;
    }
    else {
      local_1c = auStack_c8;
    }
    uVar3 = *(ushort *)(local_14 + 0x48);
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(local_1c,&DAT_00896ce8);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,uVar3);
  }
  if (&stack0x00000000 == (undefined1 *)0xd8) {
    local_20 = (undefined1 *)0x0;
  }
  else {
    local_20 = auStack_c8;
  }
  FUN_00574730(local_20,local_14 + 0x30);
  GetPolicy(param_1);
  local_24 = local_24 | 1;
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  return param_1;
}

