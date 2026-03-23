
void FUN_004baad0(short param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined4 local_3c;
  int local_38;
  int local_34;
  uint local_30;
  int *local_2c;
  uint local_28;
  int local_24;
  int *local_20;
  int local_1c;
  undefined1 local_18 [4];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849a88;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  vector<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  uVar2 = FUN_00416410();
  FUN_004bae50(uVar2);
  local_28 = 0;
  local_30 = 0;
  local_24 = FUN_005771b0(param_1);
  if (local_24 == 0) {
    if (param_1 != 0) {
      local_8 = 0xffffffff;
      FUN_0041fe20();
      ExceptionList = local_10;
      return;
    }
  }
  else {
    local_28 = (uint)*(ushort *)(local_24 + 0x28);
    local_30 = (uint)*(byte *)(local_24 + 0x68);
  }
  local_34 = local_28 << 0x10;
  FUN_0046b430(&local_3c,&local_34);
  local_38 = local_28 * 0x10000 + 0xffff;
  FUN_004bae20(local_40,&local_38);
  local_14 = local_3c;
  while (cVar1 = FUN_00420f10(local_40), cVar1 != '\0') {
    iVar3 = FUN_00422150();
    if (*(int *)(iVar3 + 4) != 0) {
      iVar3 = FUN_00422150();
      FUN_0041fe40(iVar3 + 4);
    }
    FUN_00428570();
  }
  FID_conflict_begin(local_18);
  while( true ) {
    uVar2 = FID_conflict_end(local_44);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    puVar4 = (undefined4 *)FUN_00421ec0();
    local_20 = (int *)*puVar4;
    local_1c = (**(code **)(*local_20 + 0x30))();
    if ((local_1c != 0) && (*(short *)(local_1c + 0x10) != 1)) {
      uVar5 = FUN_004b9a90();
      if ((0xffff < uVar5) && (*(int *)(local_1c + 0x84) != 7)) {
        puVar4 = (undefined4 *)FUN_00421ec0();
        local_2c = (int *)*puVar4;
        uVar5 = (**(code **)(*local_2c + 4))();
        if (uVar5 == local_30) {
          FUN_0062de40(local_1c,0x280);
        }
      }
      FUN_004b8460();
    }
    FUN_00421ee0();
  }
  local_8 = 0xffffffff;
  FUN_0041fe20();
  ExceptionList = local_10;
  return;
}

