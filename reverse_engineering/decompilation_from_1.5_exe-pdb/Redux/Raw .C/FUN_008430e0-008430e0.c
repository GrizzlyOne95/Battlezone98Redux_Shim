
/* WARNING: Removing unreachable block (ram,0x008432bc) */
/* WARNING: Removing unreachable block (ram,0x008432cc) */
/* WARNING: Removing unreachable block (ram,0x008432db) */

void FUN_008430e0(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char *pcVar6;
  int iVar7;
  undefined1 auStack_d8 [3];
  undefined1 local_d5;
  undefined4 local_d4;
  void *local_d0 [4];
  undefined4 local_c0;
  uint local_bc;
  void *local_b8 [4];
  undefined4 local_a8;
  uint local_a4;
  void *local_a0 [4];
  undefined4 local_90;
  uint local_8c;
  void *local_88 [4];
  undefined4 local_78;
  uint local_74;
  void *local_70 [4];
  undefined4 local_60;
  uint local_5c;
  void *local_58 [4];
  undefined4 local_48;
  uint local_44;
  undefined1 local_40 [24];
  void *local_28 [5];
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865d59;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)auStack_d8;
  ExceptionList = &local_c;
  local_d4 = 0;
  FUN_00840430(local_28);
  local_4 = 0;
  local_d4 = 1;
  pcVar6 = (char *)FUN_00417fd0(local_58);
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  bVar1 = false;
  local_4 = 1;
  local_d4 = 3;
  if (0xf < *(uint *)(pcVar6 + 0x14)) {
    pcVar6 = *(char **)pcVar6;
  }
  iVar7 = _stricmp(pcVar6,".exe");
  if (iVar7 != 0) {
    FUN_00840430(local_88);
    local_4 = 2;
    local_d4 = 7;
    pcVar6 = (char *)FUN_00417fd0(local_b8);
    bVar5 = true;
    bVar4 = true;
    bVar3 = false;
    bVar2 = false;
    bVar1 = false;
    local_4 = 3;
    local_d4 = 0xf;
    if (0xf < *(uint *)(pcVar6 + 0x14)) {
      pcVar6 = *(char **)pcVar6;
    }
    iVar7 = _stricmp(pcVar6,".com");
    if (iVar7 != 0) {
      FUN_00840430(local_70);
      local_4 = 4;
      local_d4 = 0x1f;
      pcVar6 = (char *)FUN_00417fd0(local_d0);
      bVar5 = true;
      bVar4 = true;
      bVar3 = true;
      bVar2 = true;
      bVar1 = false;
      local_4 = 5;
      local_d4 = 0x3f;
      if (0xf < *(uint *)(pcVar6 + 0x14)) {
        pcVar6 = *(char **)pcVar6;
      }
      iVar7 = _stricmp(pcVar6,".bat");
      if (iVar7 != 0) {
        FUN_00840430(local_a0);
        local_4 = 6;
        local_d4 = 0x7f;
        pcVar6 = (char *)FUN_00417fd0(local_40);
        bVar5 = true;
        bVar4 = true;
        bVar3 = true;
        bVar2 = true;
        bVar1 = true;
        local_4 = 7;
        local_d4 = 0xff;
        if (0xf < *(uint *)(pcVar6 + 0x14)) {
          pcVar6 = *(char **)pcVar6;
        }
        iVar7 = _stricmp(pcVar6,".cmd");
        local_d5 = 0;
        if (iVar7 != 0) goto LAB_008432b8;
      }
    }
  }
  local_d5 = 1;
LAB_008432b8:
  if (bVar1) {
    if (7 < local_8c) {
      operator_delete(local_a0[0]);
    }
    local_8c = 7;
    local_90 = 0;
    local_a0[0] = (void *)((uint)local_a0[0] & 0xffff0000);
  }
  if (bVar2) {
    if (0xf < local_bc) {
      operator_delete(local_d0[0]);
    }
    local_bc = 0xf;
    local_c0 = 0;
    local_d0[0] = (void *)((uint)local_d0[0] & 0xffffff00);
  }
  if (bVar3) {
    if (7 < local_5c) {
      operator_delete(local_70[0]);
    }
    local_5c = 7;
    local_60 = 0;
    local_70[0] = (void *)((uint)local_70[0] & 0xffff0000);
  }
  if (bVar4) {
    if (0xf < local_a4) {
      operator_delete(local_b8[0]);
    }
    local_a4 = 0xf;
    local_a8 = 0;
    local_b8[0] = (void *)((uint)local_b8[0] & 0xffffff00);
  }
  if (bVar5) {
    if (7 < local_74) {
      operator_delete(local_88[0]);
    }
    local_74 = 7;
    local_78 = 0;
    local_88[0] = (void *)((uint)local_88[0] & 0xffff0000);
  }
  if (0xf < local_44) {
    operator_delete(local_58[0]);
  }
  local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
  local_44 = 0xf;
  local_48 = 0;
  if (7 < local_14) {
    operator_delete(local_28[0]);
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

