
void FUN_0041e660(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  int *local_10;
  undefined4 local_8;
  
  puVar2 = (undefined4 *)FID_conflict_begin(local_18);
  local_8 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_end(local_1c);
  local_14 = *puVar2;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_14);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)get();
    local_10 = (int *)*puVar2;
    (**(code **)(*local_10 + 0x24))();
    FUN_00421f70();
  }
  return;
}

