
void FUN_0041dbe0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int *local_18;
  int *local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_24 = DAT_00920ef4;
  DAT_00920ef4 = DAT_00920ef4 - 0.005;
  uVar2 = FUN_004d9b40();
  *(undefined4 *)(local_8 + 0xb8) = uVar2;
  puVar3 = (undefined4 *)FID_conflict_begin(local_28);
  local_c = *puVar3;
  puVar3 = (undefined4 *)FID_conflict_end(local_2c);
  local_1c = *puVar3;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_1c);
    if (cVar1 == '\0') break;
    puVar3 = (undefined4 *)get();
    local_14 = (int *)*puVar3;
    (**(code **)(*local_14 + 0xc))();
    FUN_00421f70();
  }
  puVar3 = (undefined4 *)FID_conflict_begin(local_30);
  local_10 = *puVar3;
  puVar3 = (undefined4 *)FID_conflict_end(local_34);
  local_20 = *puVar3;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_20);
    if ((cVar1 == '\0') || (*(char *)(local_8 + 8) != '\0')) break;
    puVar3 = (undefined4 *)get();
    local_18 = (int *)*puVar3;
    (**(code **)(*local_18 + 0xc))();
    FUN_00421f70();
  }
  (**(code **)(**(int **)(local_8 + 0xa0) + 0xc))();
  DAT_00920ef4 = local_24;
  return;
}

