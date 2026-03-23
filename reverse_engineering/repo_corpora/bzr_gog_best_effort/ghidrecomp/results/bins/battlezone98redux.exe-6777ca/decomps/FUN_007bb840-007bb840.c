
undefined1 FUN_007bb840(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  allocator<char> *this;
  undefined1 *puStack_64;
  undefined1 *puStack_60;
  uint uStack_5c;
  undefined1 local_58 [16];
  undefined1 local_48 [8];
  undefined1 local_40 [8];
  undefined1 local_38 [8];
  undefined1 *local_30;
  undefined1 *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  uint local_1c;
  int local_18;
  undefined1 local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008617e1;
  local_10 = ExceptionList;
  uStack_5c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c = 0;
  puStack_60 = (undefined1 *)0x7bb877;
  FUN_007bb040();
  puStack_60 = (undefined1 *)0x2;
  puStack_64 = *(undefined1 **)(local_18 + 0x10);
  iVar2 = operator&();
  if (iVar2 == 2) {
    puStack_60 = (undefined1 *)0x2;
    puStack_64 = (undefined1 *)0x7bb894;
    puStack_60 = (undefined1 *)FUN_007bb7c0();
    puStack_64 = (undefined1 *)(local_18 + 0x10);
    operator&=();
    ExceptionList = local_10;
    return 0;
  }
  puStack_60 = (undefined1 *)0x7bb8b4;
  FUN_006673e0();
  puStack_60 = (undefined1 *)0x1;
  puStack_64 = *(undefined1 **)(local_18 + 0x10);
  iVar2 = operator&();
  if (iVar2 != 1) {
    puStack_60 = (undefined1 *)param_1;
    puStack_64 = local_58;
    FUN_007bd050();
    FUN_0066add0();
    puStack_60 = (undefined1 *)FUN_007bb6e0();
    puStack_64 = (undefined1 *)0x7bb8f1;
    FUN_00450be0();
    puStack_60 = (undefined1 *)0x7bb8f9;
    iVar2 = FUN_00667170();
    if (iVar2 != 0) {
      ExceptionList = local_10;
      return 0;
    }
  }
  puStack_60 = (undefined1 *)0x1;
  puStack_64 = *(undefined1 **)(local_18 + 0x10);
  iVar2 = operator&();
  if (iVar2 != 1) {
    local_2c = (undefined1 *)&puStack_64;
    FUN_007bb540(local_40);
    cVar1 = FUN_007bb570();
    if (cVar1 != '\0') {
      ExceptionList = local_10;
      return 0;
    }
  }
  puStack_60 = (undefined1 *)param_1;
  puStack_64 = local_48;
  FUN_007bd050();
  FUN_0066add0();
  FUN_006674d0();
  puStack_60 = (undefined1 *)0x7bb964;
  iVar2 = FUN_00667170();
  if (iVar2 != 0) {
    ExceptionList = local_10;
    return 0;
  }
  local_30 = (undefined1 *)&puStack_64;
  FUN_007bb540(local_48);
  cVar1 = FUN_007679d0();
  if (cVar1 == '\0') {
    ExceptionList = local_10;
    return 0;
  }
  puStack_60 = (undefined1 *)param_1;
  puStack_64 = (undefined1 *)0x7bb99b;
  FUN_007bd050();
  puStack_64 = (undefined1 *)0x7bb9a2;
  this = (allocator<char> *)FUN_0066add0();
  puStack_64 = (undefined1 *)0x7bb9a9;
  puStack_64 = (undefined1 *)std::allocator<char>::allocator<char>(this);
  FUN_006675b0();
  local_8 = 0;
  puStack_60 = (undefined1 *)0x7bb9c1;
  cVar1 = FUN_004c85a0();
  if (cVar1 != '\0') {
    puStack_60 = (undefined1 *)0x7bb9d0;
    puStack_60 = (undefined1 *)FUN_00667590();
    local_8 = CONCAT31(local_8._1_3_,1);
    local_1c = local_1c | 1;
    puStack_64 = local_38;
    local_28 = puStack_60;
    local_24 = puStack_60;
    cVar1 = FUN_0066e6d0();
    if (cVar1 != '\0') {
      local_20 = 1;
      goto LAB_007bba0d;
    }
  }
  local_20 = 0;
LAB_007bba0d:
  local_11 = (char)local_20;
  local_8 = 0;
  if ((local_1c & 1) != 0) {
    local_1c = local_1c & 0xfffffffe;
    puStack_60 = (undefined1 *)0x7bba2e;
    FUN_00667660();
  }
  if (local_11 == '\0') {
    local_8 = 0xffffffff;
    puStack_60 = (undefined1 *)0x7bba78;
    FUN_00667660();
    ExceptionList = local_10;
    return 0;
  }
  puStack_60 = local_38;
  puStack_64 = (undefined1 *)0x7bba42;
  FUN_007bd070();
  *(int *)(local_18 + 0xc) = *(int *)(local_18 + 0xc) + 1;
  local_12 = 1;
  local_8 = 0xffffffff;
  puStack_60 = (undefined1 *)0x7bba64;
  FUN_00667660();
  ExceptionList = local_10;
  return local_12;
}

