
void FUN_004d4b40(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_00422170();
  local_c = DAT_00917a68;
  puVar2 = (undefined4 *)FID_conflict_begin(local_14);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_1c);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00421ec0();
    local_10 = (int *)*puVar2;
    (**(code **)(*local_10 + 0x34))(param_1);
    FUN_0046b260(local_18,0);
  }
  return;
}

