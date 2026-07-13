
void FUN_005d7370(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int *piVar4;
  bool bVar5;
  undefined1 local_84 [4];
  undefined4 local_80;
  undefined1 local_7c [4];
  uint local_78;
  int *local_74;
  undefined4 local_70;
  undefined4 local_6c;
  void *local_68;
  uint local_64;
  undefined4 local_60;
  undefined4 local_5c;
  int *local_58;
  undefined1 local_54 [4];
  byte *local_50;
  byte *local_4c;
  byte local_46;
  byte local_45;
  int *local_44;
  char local_3d;
  byte local_3c [40];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ca8c;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_3d = FUN_004ce2f0(param_1,local_3c,0x28,local_14);
  if (DAT_00917b20 < 0x3ea) {
    local_3d = FUN_004ce4e0(param_1,&local_5c,4);
  }
  else {
    local_3d = FUN_004cf7b0(param_1,&local_5c,4);
  }
  local_44 = (int *)0x0;
  FUN_0042d8c0(local_54);
  do {
    uVar2 = FID_conflict_begin(local_84);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') {
LAB_005d74a9:
      if (local_44 == (int *)0x0) {
        FUN_007d6c70("No mission class matches \"%s\"\nUsing LuaMission as a substitute\n",local_3c)
        ;
        local_44 = (int *)FUN_00508dc0();
      }
      local_3d = (**(code **)(*local_44 + 4))(param_1);
      if (local_3d == '\0') {
        FUN_004cc780();
        local_74 = local_44;
        local_58 = local_44;
        if (local_44 == (int *)0x0) {
          local_6c = 0;
        }
        else {
          local_6c = (**(code **)*local_44)(1);
        }
      }
      else {
        local_68 = operator_new(8);
        local_8 = 0;
        if (local_68 == (void *)0x0) {
          local_60 = 0;
        }
        else {
          local_60 = FUN_004cc910(local_5c,local_44);
        }
        local_70 = local_60;
        local_8 = 0xffffffff;
        local_80 = local_60;
      }
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    puVar3 = (undefined4 *)FUN_0042de50();
    local_50 = *(byte **)*puVar3;
    local_4c = local_3c;
    do {
      local_46 = *local_4c;
      bVar5 = local_46 < *local_50;
      if (local_46 != *local_50) {
LAB_005d747c:
        local_64 = -(uint)bVar5 | 1;
        goto LAB_005d7484;
      }
      if (local_46 == 0) break;
      local_45 = local_4c[1];
      bVar5 = local_45 < local_50[1];
      if (local_45 != local_50[1]) goto LAB_005d747c;
      local_4c = local_4c + 2;
      local_50 = local_50 + 2;
    } while (local_45 != 0);
    local_64 = 0;
LAB_005d7484:
    local_78 = local_64;
    if (local_64 == 0) {
      piVar4 = (int *)FUN_0042de50();
      local_44 = (int *)(**(code **)(*piVar4 + 8))();
      goto LAB_005d74a9;
    }
    FUN_00438c10(local_7c,0);
  } while( true );
}

