
void FUN_004d9da0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [8];
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  if (DAT_02a0db24 < 0x33) {
    local_1c = 0;
    local_20 = 0;
    local_10 = 0;
    local_14 = 0;
    local_2c = 0xffffffff;
    local_28 = 0xfffff;
    local_24 = DAT_00917a74;
    local_18 = local_28;
    FUN_00422170();
    puVar2 = (undefined4 *)FID_conflict_begin(local_34);
    local_c = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_3c);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_00421ec0();
      local_8 = *piVar4;
      iVar5 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
      if (*(int *)(iVar5 + 0x14) == 0x53435250) {
        local_1c = local_1c + 1;
        iVar5 = FUN_00462450();
        if (iVar5 < local_18) {
          local_18 = FUN_00462450();
          local_10 = local_8;
        }
      }
      else {
        cVar1 = FUN_004631d0(local_8);
        if (cVar1 != '\0') {
          local_20 = local_20 + 1;
          iVar5 = FUN_00462450();
          if (iVar5 < local_28) {
            local_28 = FUN_00462450();
            local_14 = local_8;
          }
        }
      }
      FUN_0046b260(local_38,0);
    }
    if ((DAT_02a0db24 / 2 < local_1c) && (local_10 != 0)) {
      (**(code **)(*(int *)(local_10 + 0x18) + 0x10))();
    }
    if ((DAT_02a0db24 / 2 < local_20) && (local_14 != 0)) {
      (**(code **)(*(int *)(local_14 + 0x18) + 0x10))();
    }
  }
  return;
}

