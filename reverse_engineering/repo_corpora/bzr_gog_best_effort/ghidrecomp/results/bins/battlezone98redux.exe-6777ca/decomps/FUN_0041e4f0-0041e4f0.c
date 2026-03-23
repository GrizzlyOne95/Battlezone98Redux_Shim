
undefined1 FUN_0041e4f0(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined4 local_28;
  undefined4 local_24;
  undefined1 local_20;
  int *local_1c;
  int *local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  char local_6;
  char local_5;
  
  local_6 = '\0';
  local_5 = '\0';
  puVar2 = (undefined4 *)FID_conflict_begin(local_2c);
  local_10 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_end(local_30);
  local_24 = *puVar2;
  while (cVar1 = FID_conflict_operator__(&local_24), cVar1 != '\0') {
    puVar2 = (undefined4 *)get();
    local_18 = (int *)*puVar2;
    cVar1 = (**(code **)(*local_18 + 0x20))(param_1,param_2,param_3,0,1);
    if (cVar1 != '\0') {
      local_5 = '\x01';
    }
    FUN_00421f70();
  }
  puVar2 = (undefined4 *)FID_conflict_begin(local_34);
  local_14 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_end(local_38);
  local_28 = *puVar2;
  while (cVar1 = FID_conflict_operator__(&local_28), cVar1 != '\0') {
    puVar2 = (undefined4 *)get();
    local_1c = (int *)*puVar2;
    cVar1 = (**(code **)(*local_1c + 0x20))(param_1,param_2,param_3,local_5,0);
    if (cVar1 != '\0') {
      local_6 = '\x01';
    }
    if (*(char *)(local_c + 8) != '\0') break;
    FUN_00421f70();
  }
  if ((local_5 == '\0') && (local_6 == '\0')) {
    FUN_004b6210(param_1);
  }
  if ((local_5 == '\0') && (local_6 == '\0')) {
    local_20 = 0;
  }
  else {
    local_20 = 1;
  }
  return local_20;
}

