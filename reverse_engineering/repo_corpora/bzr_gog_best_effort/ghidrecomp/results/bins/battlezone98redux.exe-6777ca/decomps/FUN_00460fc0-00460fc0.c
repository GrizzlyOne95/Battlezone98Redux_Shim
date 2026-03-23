
undefined4 FUN_00460fc0(byte *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  bool bVar4;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  uint local_20;
  uint local_1c;
  int *local_18;
  byte *local_14;
  byte *local_10;
  undefined4 local_c;
  byte local_6;
  byte local_5;
  
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_24);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_2c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_0042de50();
    local_18 = (int *)*puVar2;
    if (*local_18 != 0) {
      local_14 = param_1;
      local_10 = (byte *)*local_18;
      do {
        local_5 = *local_10;
        bVar4 = local_5 < *local_14;
        if (local_5 != *local_14) {
LAB_00461071:
          local_1c = -(uint)bVar4 | 1;
          goto LAB_00461079;
        }
        if (local_5 == 0) break;
        local_6 = local_10[1];
        bVar4 = local_6 < local_14[1];
        if (local_6 != local_14[1]) goto LAB_00461071;
        local_10 = local_10 + 2;
        local_14 = local_14 + 2;
      } while (local_6 != 0);
      local_1c = 0;
LAB_00461079:
      local_20 = local_1c;
      if (local_1c == 0) break;
    }
    FUN_00438c10(local_28,0);
  }
  uVar3 = FID_conflict_begin(local_30);
  cVar1 = FUN_004221b0(uVar3);
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)FUN_0042de50();
    uVar3 = *puVar2;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

