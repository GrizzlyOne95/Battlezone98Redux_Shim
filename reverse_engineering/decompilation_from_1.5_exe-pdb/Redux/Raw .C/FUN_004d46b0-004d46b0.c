
void FUN_004d46b0(char param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int *local_8;
  
  FUN_00422170();
  local_10 = DAT_00917a68;
  local_14 = DAT_00920ef4;
  puVar2 = (undefined4 *)FID_conflict_begin(local_18);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_20);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    local_8 = (int *)FUN_00421ec0();
    local_8 = (int *)*local_8;
    if (((*(byte *)((int)local_8 + 0x25) >> 3 & 1) != 0) &&
       (((char)local_8[9] == param_1 || (*(byte *)(local_8 + 9) == 0xffffffff)))) {
      (**(code **)(*local_8 + 0x24))();
      DAT_00920ef4 = local_14;
    }
    FUN_0046b260(local_1c,0);
  }
  return;
}

