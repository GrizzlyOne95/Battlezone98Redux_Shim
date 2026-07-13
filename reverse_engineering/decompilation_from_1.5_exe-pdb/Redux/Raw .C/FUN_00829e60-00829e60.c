
void FUN_00829e60(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uStack_40;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00865270;
  local_10 = ExceptionList;
  uStack_40 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_40;
  ExceptionList = &local_10;
  uVar2 = 1;
  Getal(&local_15);
  iVar1 = allocate(uVar2);
  if (param_1 == 0) {
    param_1 = iVar1;
    param_2 = iVar1;
  }
  local_8 = 0;
  uVar2 = FUN_00417780(iVar1);
  Getal(&local_16);
  puVar3 = &param_1;
  uVar2 = FUN_00417780(uVar2,puVar3);
  construct<>(uVar2,puVar3);
  uVar2 = FUN_004242e0(iVar1);
  Getal(&local_17);
  puVar3 = &param_2;
  uVar2 = FUN_00417780(uVar2,puVar3);
  construct<>(uVar2,puVar3);
  FUN_00829f58();
  return;
}

