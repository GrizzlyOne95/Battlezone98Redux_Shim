
void FUN_006a2060(void)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int *local_14;
  undefined *local_10;
  undefined1 local_c [4];
  int local_8;
  
  local_10 = &DAT_009b63fc;
  FID_conflict_begin(local_c);
  while( true ) {
    uVar2 = FID_conflict_end(local_1c);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') {
      iVar5 = FUN_00417c70();
      if (iVar5 != 0) {
        iVar5 = FUN_00417c70();
        local_14 = (int *)(iVar5 + 0x18);
        puVar4 = (undefined4 *)(**(code **)(*local_14 + 0xc))();
        DAT_02c00ab0 = *puVar4;
        DAT_02c00ab4 = puVar4[1];
        DAT_02c00ab8 = puVar4[2];
      }
      return;
    }
    piVar3 = (int *)FUN_00421ec0();
    local_8 = *piVar3;
    uVar2 = (**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
    cVar1 = FUN_00466d40(uVar2);
    if (cVar1 == '\0') break;
    FUN_0046b260(local_18,0);
  }
  puVar4 = (undefined4 *)(**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
  DAT_02c00ab0 = *puVar4;
  DAT_02c00ab4 = puVar4[1];
  DAT_02c00ab8 = puVar4[2];
  return;
}

