
void FUN_0058e7e0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  local_18 = DAT_02a13ca4;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_1c);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_20);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_8 = *piVar4;
    FUN_0058d870(*(undefined4 *)(local_8 + 0x24),*(undefined4 *)(local_8 + 0x28));
    if (*(int *)(local_8 + 0x30) != 0) {
      FUN_0058d7e0(*(undefined4 *)(local_8 + 0x24),*(undefined4 *)(local_8 + 0x28),
                   *(undefined4 *)(*(int *)(local_8 + 0x30) + 0x24),
                   *(undefined4 *)(*(int *)(local_8 + 0x30) + 0x28));
    }
    for (local_10 = FUN_0058d440(local_8); -1 < local_10; local_10 = FUN_0058d470(local_10)) {
      local_14 = FUN_0058d4a0(local_10);
      if (*(int *)(local_14 + 0x30) == 0) {
        FUN_0058d7e0(*(undefined4 *)(local_8 + 0x24),*(undefined4 *)(local_8 + 0x28),
                     *(undefined4 *)(local_14 + 0x24),*(undefined4 *)(local_14 + 0x28));
      }
    }
    FUN_00421ee0();
  }
  return;
}

