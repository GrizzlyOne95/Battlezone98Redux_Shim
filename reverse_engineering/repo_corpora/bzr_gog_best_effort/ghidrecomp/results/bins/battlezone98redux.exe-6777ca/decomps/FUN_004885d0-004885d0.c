
undefined4 FUN_004885d0(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 local_20 [4];
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00848f78;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_00420350(local_14,&stack0x00000004);
  uVar3 = FID_conflict_begin(local_20);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    local_1c = 0;
    local_8 = 0xffffffff;
    ~basic_string<>(uVar2);
    local_18 = local_1c;
  }
  else {
    FUN_00422150();
    local_18 = size();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  return local_18;
}

