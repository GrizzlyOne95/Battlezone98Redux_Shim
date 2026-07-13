
void FUN_004dfd70(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  undefined4 local_8;
  
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_10);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_18);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_c = *piVar4;
    FUN_004d97d0();
    *(undefined4 *)(local_c + 0xe8) = 0x3f800000;
    FUN_0046b260(local_14,0);
  }
  return;
}

