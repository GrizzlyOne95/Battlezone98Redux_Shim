
void FUN_00417fd0(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  uint local_34;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a78;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_34 = 0;
  basic_string<>(local_14);
  local_8 = 0;
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    puVar5 = local_2c;
    FID_conflict_begin(local_38);
    iVar2 = get(puVar5);
    iVar3 = FUN_004170c0();
    iVar2 = iVar2 + iVar3 * 2;
    FID_conflict_begin(local_3c);
    uVar4 = get(iVar2);
    FUN_004180f0(uVar4);
  }
  basic_string<>(local_2c);
  local_34 = local_34 | 1;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

