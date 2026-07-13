
void FUN_00577510(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined4 uVar6;
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  int local_30;
  int local_2c;
  undefined2 *local_28;
  int local_24;
  char *local_20;
  undefined1 local_19;
  undefined4 local_18;
  undefined2 local_14;
  char local_12 [10];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = &local_14;
  local_14 = 0x5353;
  local_20 = local_12;
  local_12[0] = '\0';
  local_19 = 1;
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_00420260(local_3c);
  local_18 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_34);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    iVar4 = FUN_00423870();
    if ((*(int *)(iVar4 + 0x10) == 0) ||
       (iVar4 = FUN_00423870(), *(short *)(*(int *)(iVar4 + 0x10) + 0x28) == DAT_009180d4)) {
      *local_20 = *local_20 + '\x01';
    }
    else {
      iVar4 = FUN_00423870();
      local_2c = *(int *)(iVar4 + 0x10);
      if (*(int *)(local_2c + 0x58) != 0 || *(int *)(local_2c + 0x5c) != 0) {
        *local_20 = *local_20 + '\x01';
      }
    }
    FUN_004305b0(local_48,0);
  }
  puVar2 = (undefined4 *)FUN_00420260(local_44);
  local_18 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_40);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    iVar4 = FUN_00423870();
    if ((*(int *)(iVar4 + 0x10) != 0) &&
       (iVar4 = FUN_00423870(), *(short *)(*(int *)(iVar4 + 0x10) + 0x28) != DAT_009180d4)) {
      iVar4 = FUN_00423870();
      local_30 = *(int *)(iVar4 + 0x10);
      if (*(int *)(local_30 + 0x60) == 0 && *(int *)(local_30 + 100) == 0) {
        local_24 = FUN_007659f0();
        if (local_24 != 0) {
          uVar6 = 0;
          uVar3 = 3;
          puVar5 = &local_14;
          iVar4 = FUN_00422150(puVar5,3,0);
          FUN_00759710(*(int *)(iVar4 + 0x10) + 0x30,puVar5,uVar3,uVar6);
        }
        local_19 = 0;
      }
    }
    FUN_004305b0(local_38,0);
  }
  FUN_0083e885();
  return;
}

