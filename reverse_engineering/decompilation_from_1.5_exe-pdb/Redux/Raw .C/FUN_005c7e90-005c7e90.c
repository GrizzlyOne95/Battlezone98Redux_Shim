
undefined4 FUN_005c7e90(byte *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  bool bVar4;
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined4 local_28;
  uint local_24;
  undefined4 local_20;
  uint local_1c;
  undefined4 local_18;
  byte *local_14;
  byte *local_10;
  undefined4 local_c;
  byte local_6;
  byte local_5;
  
  local_18 = DAT_00917a74;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_2c);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_34);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00421ec0();
    local_20 = *puVar2;
    local_14 = param_1;
    local_10 = (byte *)FUN_004623e0();
    do {
      local_5 = *local_10;
      bVar4 = local_5 < *local_14;
      if (local_5 != *local_14) {
LAB_005c7f3e:
        local_1c = -(uint)bVar4 | 1;
        goto LAB_005c7f46;
      }
      if (local_5 == 0) break;
      local_6 = local_10[1];
      bVar4 = local_6 < local_14[1];
      if (local_6 != local_14[1]) goto LAB_005c7f3e;
      local_10 = local_10 + 2;
      local_14 = local_14 + 2;
    } while (local_6 != 0);
    local_1c = 0;
LAB_005c7f46:
    local_24 = local_1c;
    if (local_1c == 0) break;
    FUN_0046b260(local_30,0);
  }
  uVar3 = FID_conflict_end(local_38);
  cVar1 = FID_conflict_operator__(uVar3);
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)FUN_00421ec0();
    local_28 = *puVar2;
    uVar3 = FUN_00477590(local_28);
  }
  else {
    FUN_007d6a70("No object named \"%s\"",param_1);
    uVar3 = 0;
  }
  return uVar3;
}

