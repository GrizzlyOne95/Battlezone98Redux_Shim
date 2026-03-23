
int FUN_006f6570(int param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008556c8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006f6af0(param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  uVar2 = FID_conflict_end(local_18);
  FID_conflict_begin(local_1c);
  uVar1 = FID_conflict_operator__(uVar2);
  *(undefined1 *)(local_14 + 0xc) = uVar1;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(local_14 + 0x10));
  puVar3 = (undefined4 *)FID_conflict_begin(local_20);
  *(undefined4 *)(local_14 + 0x18) = *puVar3;
  iVar4 = eof(param_1);
  *(int *)(local_14 + 0x1c) = iVar4;
  if (*(char *)(local_14 + 0xc) == '\0') {
    FID_conflict_begin(local_24);
    puVar3 = (undefined4 *)FUN_00421ec0();
    uVar2 = puVar3[1];
    *(undefined4 *)(local_14 + 0x10) = *puVar3;
    *(undefined4 *)(local_14 + 0x14) = uVar2;
    FUN_00496680();
  }
  ExceptionList = local_10;
  return local_14;
}

