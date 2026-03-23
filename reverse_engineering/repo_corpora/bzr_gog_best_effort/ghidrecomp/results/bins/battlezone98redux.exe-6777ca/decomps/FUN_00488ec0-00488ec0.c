
undefined4 FUN_00488ec0(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00848f78;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uVar3 = FID_conflict_begin(local_1c);
  FUN_00420350(local_20,&stack0x00000004);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    local_18 = 0;
    local_8 = 0xffffffff;
    ~basic_string<>(uVar2);
    local_14 = local_18;
  }
  else {
    puVar4 = (undefined4 *)FUN_0048a3b0(&stack0x00000004);
    local_14 = *puVar4;
    local_8 = 0xffffffff;
    ~basic_string<>(uVar2);
  }
  ExceptionList = local_10;
  return local_14;
}

