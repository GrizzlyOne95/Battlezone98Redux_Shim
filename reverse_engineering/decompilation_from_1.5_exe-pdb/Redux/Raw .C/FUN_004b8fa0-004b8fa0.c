
void FUN_004b8fa0(short param_1,undefined4 param_2,undefined2 param_3,int param_4)

{
  short sVar1;
  char cVar2;
  short sVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 local_6c [8];
  undefined1 local_64 [8];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  int local_3c;
  int *local_38;
  int *local_34;
  int *local_30;
  int *local_2c;
  int *local_28;
  int local_24;
  uint local_20;
  int local_1c;
  int *local_18;
  int local_14;
  undefined4 local_10;
  int *local_c;
  byte local_5;
  
  FUN_00430590();
  local_24 = param_4;
  local_5 = *(byte *)(param_4 + 1);
  local_14 = *(int *)(param_4 + 2);
  puVar4 = (undefined4 *)FUN_0046b370(local_40,&local_14);
  local_10 = *puVar4;
  uVar5 = FID_conflict_begin(local_44);
  cVar2 = FUN_00420f10(uVar5);
  if (cVar2 == '\0') {
    local_28 = (int *)0x0;
  }
  else {
    iVar6 = FUN_00422150();
    local_28 = *(int **)(iVar6 + 4);
  }
  local_c = local_28;
  if (local_28 == (int *)0x0) {
    uVar5 = make_pair<>(local_48,&param_1,&param_3);
    FUN_004bc550(uVar5);
    local_18 = (int *)FUN_004baec0(local_64);
    if (*local_18 == 0) {
      *local_18 = local_14;
    }
    else if (*local_18 != local_14) {
      puVar4 = (undefined4 *)FUN_0046b370(local_4c,local_18);
      local_10 = *puVar4;
      uVar5 = FID_conflict_begin(local_50);
      cVar2 = FUN_00420f10(uVar5);
      if (cVar2 == '\0') {
        local_2c = (int *)0x0;
      }
      else {
        iVar6 = FUN_00422150();
        local_2c = *(int **)(iVar6 + 4);
      }
      local_c = local_2c;
      if (local_2c != (int *)0x0) {
        if (local_2c == (int *)0x0) {
          local_30 = (int *)0x0;
        }
        else {
          local_30 = local_2c + -6;
        }
        local_30[0x3b] = 0;
        *(undefined1 *)(local_2c + 0x1a) = 0;
        *(undefined2 *)((int)local_2c + 0x62) = 0;
        FUN_004badc0(local_2c + 0x19);
        (**(code **)(*local_c + 0x10))();
      }
      *local_18 = local_14;
    }
    puVar4 = (undefined4 *)FUN_0046b370(local_54,&local_14);
    local_10 = *puVar4;
    uVar5 = FID_conflict_begin(local_58);
    cVar2 = FUN_00420f10(uVar5);
    if (cVar2 == '\0') {
      local_34 = (int *)0x0;
    }
    else {
      iVar6 = FUN_00422150();
      local_34 = *(int **)(iVar6 + 4);
    }
    local_c = local_34;
    if ((local_34 != (int *)0x0) && ((local_5 & 3) == 1)) {
      if (local_34 == (int *)0x0) {
        local_38 = (int *)0x0;
      }
      else {
        local_38 = local_34 + -6;
      }
      local_38[0x3b] = 0;
      local_1c = (**(code **)(*local_34 + 0x30))();
      if (((int)(uint)local_5 >> 6 & 1U) == 0) {
        if (local_1c != 0) {
          local_20 = (int)(uint)local_5 >> 2 & 0xf;
          if (local_20 == 3) {
            FUN_0062de40(local_1c,&DAT_01800280);
          }
          else if (local_20 == 2) {
            FUN_0062de40(local_1c,&DAT_01400280);
          }
          else if (local_20 == 0) {
            FUN_0062de40(local_1c,0x280);
          }
          else {
            FUN_0062de40(local_1c,&DAT_01000280);
          }
        }
      }
      else {
        (**(code **)(*local_c + 0x24))();
      }
      *(undefined1 *)(local_c + 0x1a) = 0;
      *(undefined2 *)((int)local_c + 0x62) = 0;
      FUN_004badc0(local_c + 0x19);
      FUN_004b7bd0();
      local_3c = (**(code **)*local_c)();
      if ((local_3c != 0) && (*(int *)(local_3c + 0x14) == 0x53435250)) {
        (**(code **)(*local_c + 0x10))();
      }
    }
    sVar1 = param_1;
    if ((local_5 & 3) == 0) {
      sVar3 = FUN_00572d90();
      if (sVar1 != sVar3) {
        if (local_c == (int *)0x0) {
          FUN_004b9350(param_1,param_4,param_2);
          puVar4 = (undefined4 *)FUN_004bad10(&local_14);
          local_c = (int *)*puVar4;
        }
        if (local_c != (int *)0x0) {
          FUN_004b7e60(param_1,param_3,param_4,param_2);
        }
      }
    }
    else {
      uVar5 = make_pair<>(local_5c,&param_1,&param_3);
      FUN_004bc550(uVar5);
      FUN_004baf80(local_6c);
    }
  }
  return;
}

