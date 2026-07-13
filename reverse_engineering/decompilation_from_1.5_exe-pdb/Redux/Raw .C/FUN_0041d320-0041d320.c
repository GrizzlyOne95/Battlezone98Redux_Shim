
void __fastcall FUN_0041d320(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined4 local_3c;
  undefined4 *local_38;
  undefined4 local_34;
  undefined4 *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 local_18;
  undefined4 *local_14;
  undefined4 local_10;
  undefined4 *local_c;
  int local_8;
  
  *(undefined1 *)(param_1 + 8) = 1;
  local_8 = param_1;
  puVar2 = (undefined4 *)FID_conflict_begin(local_40);
  local_10 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_end(local_44);
  local_20 = *puVar2;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_20);
    if (cVar1 == '\0') break;
    piVar3 = (int *)get();
    local_24 = (undefined4 *)*piVar3;
    local_c = local_24;
    if (local_24 == (undefined4 *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = (**(code **)*local_24)(1);
    }
    FUN_00421f70();
  }
  FUN_0041ff50();
  puVar2 = (undefined4 *)FID_conflict_begin(local_48);
  local_18 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_end(local_4c);
  local_2c = *puVar2;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_2c);
    if (cVar1 == '\0') break;
    piVar3 = (int *)get();
    local_30 = (undefined4 *)*piVar3;
    local_14 = local_30;
    if (local_30 == (undefined4 *)0x0) {
      local_34 = 0;
    }
    else {
      local_34 = (**(code **)*local_30)(1);
    }
    FUN_00421f70();
  }
  FUN_0041ff50();
  local_38 = *(undefined4 **)(local_8 + 0xa0);
  local_1c = local_38;
  if (local_38 == (undefined4 *)0x0) {
    local_3c = 0;
  }
  else {
    local_3c = (**(code **)*local_38)(1);
  }
  *(undefined4 *)(local_8 + 0xa0) = 0;
  FUN_0041ff50();
  _Val_type<>(0);
  FUN_0041ff50();
  FUN_0041ff50();
  *(undefined4 *)(local_8 + 0xc) = 0;
  *(undefined1 *)(local_8 + 0x10) = 0;
  return;
}

