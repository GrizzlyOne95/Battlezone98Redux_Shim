
void FUN_00576b70(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 *puVar4;
  undefined1 local_19c [8];
  undefined1 local_194 [4];
  undefined1 local_190 [4];
  uint local_18c;
  undefined1 local_188 [4];
  uint local_184;
  int local_180;
  undefined4 local_174;
  undefined2 *local_170;
  undefined4 local_16c;
  uint local_168;
  undefined1 local_164 [4];
  undefined1 local_160 [4];
  int local_15c;
  int local_158;
  short local_154;
  int local_150;
  int local_14c;
  int local_148;
  undefined4 *local_144;
  undefined2 local_140;
  undefined4 local_13e [2];
  undefined1 local_136;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b98b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_168 = FUN_00822d90(local_14);
  FUN_00579060();
  local_8 = 0;
  local_158 = FUN_00578380();
  if (DAT_00917f48 != 0) {
    local_154 = *(short *)(DAT_00917f48 + 4);
  }
  for (local_148 = FUN_0056f950(); local_148 != 0; local_148 = FUN_00577b50(local_148)) {
    if (DAT_009180d4 != *(short *)(local_148 + 0x28)) {
      local_184 = FUN_00575f80();
      local_18c = FUN_00575ff0();
      if (((*(int *)(local_148 + 0x40) == 0) ||
          (local_168 <= (uint)(*(int *)(local_148 + 0x40) + DAT_008e8d0c))) ||
         ((local_184 <= DAT_008e8cf8 && (local_18c <= DAT_008e8bfc)))) {
        if (*(int *)(local_148 + 0x44) != 0) {
          if ((local_154 == *(short *)(local_148 + 0x28)) && (local_158 != 0)) {
            local_174 = FUN_005765e0();
          }
          else {
            local_174 = FUN_005765e0();
          }
          uVar2 = FUN_0081cb40("multi_message","stop_lagging",local_174);
          FUN_0056fcb0(uVar2);
          *(undefined4 *)(local_148 + 0x44) = 0;
        }
      }
      else {
        if (*(int *)(local_148 + 0x44) == 0) {
          if ((local_154 == *(short *)(local_148 + 0x28)) && (local_158 != 0)) {
            local_16c = FUN_005765e0();
          }
          else {
            local_16c = FUN_005765e0();
          }
          uVar2 = FUN_0081cb40("multi_message","start_lagging",local_16c);
          FUN_0056fcb0(uVar2);
          *(uint *)(local_148 + 0x44) = local_168;
        }
        iVar3 = FUN_00572a60();
        if ((iVar3 != 0) && ((uint)(*(int *)(local_148 + 0x44) + DAT_008e8ce4) < local_168)) {
          FUN_00579090(local_19c,local_148 + 0x28);
        }
      }
    }
  }
  uVar2 = 0;
  FUN_00764760(0);
  FUN_0073d860(uVar2);
  cVar1 = FUN_004202c0();
  if (cVar1 == '\0') {
    FUN_00424640(local_160);
    FID_conflict_begin(local_188);
    while (cVar1 = FUN_00420f10(local_188), cVar1 != '\0') {
      puVar4 = (undefined2 *)FUN_005790d0();
      local_15c = FUN_005771b0(*puVar4);
      if ((local_15c != 0) && (*(char *)(local_15c + 0x8e) == '\0')) {
        FUN_0081e820("Auto kicking player ",local_15c + 0x74," due to ping failure\n");
        uVar2 = FUN_0081e660();
        uVar2 = FUN_004bc590(uVar2);
        uVar2 = FUN_00574730(uVar2);
        FUN_004bc590(uVar2);
        FUN_00576a70();
      }
      FUN_00422190();
    }
  }
  if (DAT_009175be == '\0') {
    for (local_150 = FUN_0056f950(); local_150 != 0; local_150 = FUN_00577b50(local_150)) {
      if (DAT_009180d4 != *(short *)(local_150 + 0x28)) {
        FUN_00576480();
      }
    }
  }
  else {
    local_170 = &local_140;
    local_144 = local_13e;
    local_140 = 0x4147;
    local_136 = 0;
    uVar2 = FUN_00822dd0();
    local_144[1] = uVar2;
    uVar2 = FUN_00822e10(1);
    *local_144 = uVar2;
    FUN_00420260(local_164);
    while( true ) {
      uVar2 = FID_conflict_begin(local_190);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      iVar3 = FUN_00423870();
      local_14c = *(int *)(iVar3 + 0x10);
      if ((local_14c != 0) && (DAT_009180d4 != *(short *)(local_14c + 0x28))) {
        *(undefined2 *)(local_144 + (uint)*(byte *)(local_144 + 2) * 3 + 3) =
             *(undefined2 *)(local_14c + 0x28);
        if (*(char *)(local_14c + 0x8c) == '\0') {
          local_144[(uint)*(byte *)(local_144 + 2) * 3 + 4] = 0;
          local_144[(uint)*(byte *)(local_144 + 2) * 3 + 5] = 0;
        }
        else {
          local_144[(uint)*(byte *)(local_144 + 2) * 3 + 4] = *(undefined4 *)(local_14c + 4);
          if (*(int *)(local_14c + 4) == 0) {
            local_144[(uint)*(byte *)(local_144 + 2) * 3 + 5] = 1;
          }
          else {
            local_144[(uint)*(byte *)(local_144 + 2) * 3 + 5] = *(undefined4 *)(local_14c + 8);
          }
        }
        *(char *)(local_144 + 2) = *(char *)(local_144 + 2) + '\x01';
        *(undefined4 *)(local_14c + 0x4c) = *local_144;
        *(int *)(local_14c + 0x1b0) = *(int *)(local_14c + 0x1b0) << 1;
      }
      FUN_004305b0(local_194,0);
    }
    local_180 = (int)local_144 + (((uint)*(byte *)(local_144 + 2) * 0xc + 0xc) - (int)&local_140);
    FUN_00575890(&local_140,local_180,0,1);
  }
  local_8 = 0xffffffff;
  FUN_00577190();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

