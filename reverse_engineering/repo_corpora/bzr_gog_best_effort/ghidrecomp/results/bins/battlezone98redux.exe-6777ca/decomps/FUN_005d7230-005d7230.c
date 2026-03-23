
undefined4 FUN_005d7230(byte *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  bool bVar4;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  uint local_1c;
  uint local_18;
  undefined1 local_14 [4];
  byte *local_10;
  byte *local_c;
  byte local_6;
  byte local_5;
  
  FUN_0042d8c0(local_14);
  do {
    uVar2 = FID_conflict_begin(local_24);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') {
      return 0;
    }
    puVar3 = (undefined4 *)FUN_0042de50();
    local_10 = *(byte **)*puVar3;
    local_c = param_1;
    do {
      local_5 = *local_c;
      bVar4 = local_5 < *local_10;
      if (local_5 != *local_10) {
LAB_005d72c6:
        local_18 = -(uint)bVar4 | 1;
        goto LAB_005d72ce;
      }
      if (local_5 == 0) break;
      local_6 = local_c[1];
      bVar4 = local_6 < local_10[1];
      if (local_6 != local_10[1]) goto LAB_005d72c6;
      local_c = local_c + 2;
      local_10 = local_10 + 2;
    } while (local_6 != 0);
    local_18 = 0;
LAB_005d72ce:
    local_1c = local_18;
    if (local_18 == 0) {
      puVar3 = (undefined4 *)FUN_0042de50();
      return *puVar3;
    }
    FUN_00438c10(local_20,0);
  } while( true );
}

