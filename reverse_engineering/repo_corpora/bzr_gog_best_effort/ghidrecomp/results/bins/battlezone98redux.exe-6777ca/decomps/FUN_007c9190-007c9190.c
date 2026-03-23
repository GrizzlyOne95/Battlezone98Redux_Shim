
void FUN_007c9190(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  cVar1 = FUN_007c6240();
  if (cVar1 == '\0') {
    local_c = 0xe;
    uVar2 = FID_conflict_end(local_18);
    puVar5 = &local_c;
    puVar3 = (undefined4 *)FID_conflict_end(local_1c);
    uVar4 = *puVar3;
    puVar3 = (undefined4 *)FID_conflict_begin(local_20);
    FUN_0046e9c0(local_24,*puVar3,uVar4,puVar5,uVar2);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') {
      local_10 = 0xf;
      uVar2 = FID_conflict_end(local_28);
      puVar5 = &local_10;
      puVar3 = (undefined4 *)FID_conflict_end(local_2c);
      uVar4 = *puVar3;
      puVar3 = (undefined4 *)FID_conflict_begin(local_30);
      FUN_0046e9c0(local_34,*puVar3,uVar4,puVar5,uVar2);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') {
        return;
      }
    }
    FUN_0041ff50();
    local_14 = 1;
    FUN_0041ff90(&local_14);
    if (*(int *)(local_8 + 0x14) != 0) {
      FUN_005d4260();
    }
  }
  return;
}

