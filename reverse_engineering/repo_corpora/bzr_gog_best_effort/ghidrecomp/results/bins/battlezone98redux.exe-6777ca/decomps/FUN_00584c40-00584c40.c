
void FUN_00584c40(uint param_1,int param_2,undefined4 param_3,float param_4)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  uint local_1c;
  uint local_18;
  int local_14;
  int local_10;
  uint local_c;
  undefined1 local_8 [4];
  
  local_c = param_1;
  local_1c = param_1 + param_2;
  while (uVar1 = local_c, local_c < local_1c) {
    local_18 = local_c;
    local_14 = local_c + 2;
    local_c = local_c + 4;
    FUN_004bcc60(uVar1,local_14);
    FUN_00585840(local_8,local_20);
    uVar3 = FID_conflict_begin(local_24);
    cVar2 = FUN_00420f10(uVar3);
    if (cVar2 != '\0') {
      iVar4 = FUN_00422150(&param_4);
      puVar5 = (undefined4 *)FUN_00585c40(*(int *)(iVar4 + 4) + 0x78);
      iVar4 = FUN_00422150();
      *(undefined4 *)(*(int *)(iVar4 + 4) + 0x78) = *puVar5;
      if (param_4 <= 0.0) {
        iVar4 = FUN_00422150();
        local_10 = *(int *)(*(int *)(iVar4 + 4) + 0x14);
        if (local_10 != 0) {
          *(uint *)(local_10 + 0x14) = *(uint *)(local_10 + 0x14) | 0x200;
        }
      }
    }
  }
  return;
}

