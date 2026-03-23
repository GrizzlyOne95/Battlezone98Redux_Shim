
void FUN_0041d4d0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined8 uVar5;
  undefined1 local_58 [8];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  void *local_2c;
  undefined1 local_28 [4];
  int *local_24;
  int *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844f34;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = FUN_004202c0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (cVar1 != '\0') {
    FUN_0041c580();
  }
  FUN_0041c580();
  FUN_00421c40();
  local_8 = 0;
  puVar2 = (undefined4 *)FID_conflict_begin(local_40);
  local_18 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_end(local_44);
  local_34 = *puVar2;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_34);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)get();
    local_20 = (int *)*puVar2;
    (**(code **)(*local_20 + 8))(local_58);
    FUN_00421f70();
  }
  puVar2 = (undefined4 *)FID_conflict_begin(local_48);
  local_1c = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_end(local_4c);
  local_38 = *puVar2;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_38);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)get();
    local_24 = (int *)*puVar2;
    (**(code **)(*local_24 + 8))(local_58);
    FUN_00421f70();
  }
  FUN_0041d320();
  uVar5 = FUN_00689eb0();
  *(undefined8 *)(local_14 + 0xbc) = uVar5;
  FUN_0041d750(local_28);
  uVar3 = FID_conflict_begin(local_50);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 != '\0') {
    iVar4 = FUN_00421ea0();
    FUN_0041d220(local_58,iVar4 + 0x18);
  }
  FUN_0041d220(local_58,local_14 + 0xac);
  local_2c = operator_new(0x88);
  local_8._0_1_ = 1;
  if (local_2c == (void *)0x0) {
    local_30 = 0;
  }
  else {
    local_30 = FUN_00419ef0(local_58);
  }
  local_3c = local_30;
  local_8 = (uint)local_8._1_3_ << 8;
  *(undefined4 *)(local_14 + 0xa0) = local_30;
  if (*(int *)(local_14 + 0xc) != 0) {
    _Val_type<>(1);
  }
  FUN_0041e260();
  FID_conflict_operator_(local_14 + 0x2c);
  *(undefined4 *)(local_14 + 0x78) = *(undefined4 *)(local_14 + 0x74);
  *(undefined1 *)(local_14 + 8) = 0;
  local_8 = 0xffffffff;
  FUN_0041d730();
  ExceptionList = local_10;
  return;
}

