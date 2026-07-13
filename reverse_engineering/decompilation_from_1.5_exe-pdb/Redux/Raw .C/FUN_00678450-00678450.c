
void FUN_00678450(void)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined1 local_64 [4];
  int local_60;
  void *local_5c;
  void *local_58;
  undefined1 local_54 [4];
  void *local_50;
  void *local_4c;
  undefined1 local_48 [4];
  undefined4 local_44;
  undefined1 local_40 [4];
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  HardwareBufferManager *local_28;
  int local_24;
  undefined4 *local_20;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  FUN_006786f0();
  local_24 = local_8 + 0x16c;
  FID_conflict_begin(local_10);
  FID_conflict_end(local_40);
  while( true ) {
    cVar1 = FID_conflict_operator__(local_40);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00421ec0();
    local_44 = *puVar2;
    local_28 = Ogre::HardwareBufferManager::getSingletonPtr();
    (**(code **)(*(int *)local_28 + 0x40))(local_44);
    FUN_00421ee0();
  }
  FUN_0041ff50();
  local_2c = local_8 + 0x160;
  FID_conflict_begin(local_14);
  FID_conflict_end(local_48);
  while( true ) {
    cVar1 = FID_conflict_operator__(local_48);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00421ec0();
    local_50 = (void *)*puVar2;
    local_4c = local_50;
    operator_delete__(local_50);
    FUN_00421ee0();
  }
  FUN_0041ff50();
  local_30 = local_8 + 0x184;
  FID_conflict_begin(local_18);
  FID_conflict_end(local_54);
  while( true ) {
    cVar1 = FID_conflict_operator__(local_54);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00421ec0();
    local_5c = (void *)*puVar2;
    local_58 = local_5c;
    operator_delete__(local_5c);
    FUN_00421ee0();
  }
  FUN_0041ff50();
  FUN_0067acb0();
  FUN_0067ae30();
  local_60 = local_8 + 0x1c8;
  local_34 = local_8 + 0x1b0;
  for (local_c = local_34; local_c != local_60; local_c = local_c + 0xc) {
    local_3c = local_c;
    local_38 = local_c;
    FID_conflict_begin(local_1c);
    FID_conflict_end(local_64);
    while( true ) {
      cVar1 = FID_conflict_operator__(local_64);
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_00421ec0();
      local_20 = (undefined4 *)*piVar3;
      if (local_20 == (undefined4 *)0x0) {
        uVar4 = 0;
      }
      else {
        uVar4 = (**(code **)*local_20)(1);
      }
      FUN_00421ee0(uVar4);
    }
    FUN_0041ff50();
  }
  FUN_004bae50(0x400);
  FUN_004bae50(0x400);
  FUN_004bae50(0x400);
  FUN_004bae50(2);
  return;
}

