
undefined1 FUN_00773c40(undefined4 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  basic_istream<char,struct_std::char_traits<char>_> local_e8 [180];
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  int *local_20;
  uint local_1c;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e23b;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004203f0(param_1,3,1);
  local_8 = 0;
  std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
            (local_e8,(__uint64 *)&local_34);
  iVar4 = FUN_00773a50(uVar3);
  uVar1 = local_15;
  uVar2 = local_13;
  if (iVar4 == 0) {
LAB_00773d52:
    local_13 = uVar2;
    local_15 = uVar1;
    local_14 = 1;
    local_8 = 0xffffffff;
    FUN_00417f10();
    local_12 = local_14;
  }
  else {
    local_20 = (int *)FUN_00773a50(uVar3);
    local_1c = (**(code **)(*local_20 + 0xe8))(local_34,local_30);
    local_15 = (local_1c & 8) != 0;
    local_28 = (uint)(byte)local_15;
    local_13 = (local_1c & 0x10) != 0;
    local_2c = (uint)(byte)local_13;
    local_11 = (local_1c & 0x20) != 0;
    local_24 = (uint)(byte)local_11;
    if ((!(bool)local_15) && (!(bool)local_13)) {
      uVar1 = 0;
      uVar2 = 0;
      if (!(bool)local_11) goto LAB_00773d52;
    }
    local_12 = 0;
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  return local_12;
}

