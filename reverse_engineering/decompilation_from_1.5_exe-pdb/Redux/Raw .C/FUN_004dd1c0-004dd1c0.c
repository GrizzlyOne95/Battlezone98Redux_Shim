
char FUN_004dd1c0(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  int *local_1c;
  undefined4 local_18;
  int *local_14;
  int local_10;
  undefined4 local_c;
  char local_5;
  
  local_5 = 1;
  FUN_00422170();
  local_10 = size();
  puVar2 = (undefined4 *)FID_conflict_begin(local_24);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_2c);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_14 = (int *)(*piVar4 + 0x18);
    iVar5 = (**(code **)(*local_14 + 0x2c))();
    if (iVar5 == 0) {
      local_10 = local_10 + -1;
    }
    FUN_0046b260(local_28,0);
  }
  local_5 = FUN_004cd1b0(param_1,&local_10,4,&DAT_00874054);
  if (DAT_00917afc == 0) goto LAB_004dd2aa;
  if (local_5 == '\0') {
LAB_004dd29d:
    local_18 = 0;
  }
  else {
    cVar1 = FUN_004dce70(param_1,DAT_00917afc);
    if (cVar1 == '\0') goto LAB_004dd29d;
    local_18 = 1;
  }
  local_5 = (char)local_18;
LAB_004dd2aa:
  puVar2 = (undefined4 *)FID_conflict_begin(local_30);
  local_c = *puVar2;
  do {
    uVar3 = FID_conflict_end(local_38);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') {
      return local_5;
    }
    piVar4 = (int *)FUN_00421ec0();
    if (*piVar4 != DAT_00917afc) {
      piVar4 = (int *)FUN_00421ec0();
      local_1c = (int *)(*piVar4 + 0x18);
      iVar5 = (**(code **)(*local_1c + 0x2c))();
      if (iVar5 != 0) {
        if (local_5 == '\0') {
LAB_004dd34f:
          local_20 = 0;
        }
        else {
          puVar2 = (undefined4 *)FUN_00421ec0();
          cVar1 = FUN_004dce70(param_1,*puVar2);
          if (cVar1 == '\0') goto LAB_004dd34f;
          local_20 = 1;
        }
        local_5 = (char)local_20;
      }
    }
    FUN_0046b260(local_34,0);
  } while( true );
}

