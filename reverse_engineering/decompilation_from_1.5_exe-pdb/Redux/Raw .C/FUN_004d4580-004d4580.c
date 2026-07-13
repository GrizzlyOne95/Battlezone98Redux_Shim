
void FUN_004d4580(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  int *local_c;
  undefined4 local_8;
  
  FUN_00422170();
  local_10 = DAT_00917a68;
  puVar2 = (undefined4 *)FID_conflict_begin(local_14);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_1c);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    local_c = (int *)FUN_00421ec0();
    local_c = (int *)*local_c;
    if ((*(byte *)((int)local_c + 0x25) >> 1 & 1) != 0) {
      (**(code **)(*local_c + 0x1c))(param_1);
    }
    FUN_0046b260(local_18,0);
  }
  return;
}

