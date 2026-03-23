
void FUN_0058f490(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  local_10 = DAT_02a13ca4;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_14);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_18);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_c = *piVar4;
    if ((*(char *)(local_c + 0x20) == '\0') && (*(char *)(local_c + 0x1d) == '\0')) {
      FUN_0058c930(local_c);
    }
    else {
      FUN_0058ca30(local_c);
    }
    FUN_00421ee0();
  }
  FUN_0041ff50();
  FUN_0058d3b0();
  DAT_00918150 = 0;
  return;
}

