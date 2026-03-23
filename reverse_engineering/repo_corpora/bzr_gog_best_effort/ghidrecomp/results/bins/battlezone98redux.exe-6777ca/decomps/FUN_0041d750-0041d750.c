
undefined4 * FUN_0041d750(undefined4 *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  int local_8;
  
  FUN_00422170();
  puVar2 = (undefined4 *)FUN_00420350(local_10,local_8 + 0x2c);
  local_c = *puVar2;
  uVar3 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)FUN_00420350(local_18,local_8 + 0x44);
    local_c = *puVar2;
    uVar3 = FID_conflict_begin(local_1c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') {
      cVar1 = FUN_004202c0();
      if (cVar1 == '\0') {
        puVar2 = (undefined4 *)FUN_00420260(local_20);
        local_c = *puVar2;
      }
      else {
        puVar2 = (undefined4 *)FID_conflict_begin(local_24);
        local_c = *puVar2;
      }
    }
  }
  *param_1 = local_c;
  return param_1;
}

