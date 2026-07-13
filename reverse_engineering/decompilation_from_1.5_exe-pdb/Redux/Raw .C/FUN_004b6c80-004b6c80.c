
void FUN_004b6c80(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined8 uVar5;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_00917594 = FUN_00439e60();
  DAT_00917580 = *(int *)(DAT_00917594 + 0x38);
  uVar5 = FUN_00437330();
  *(int *)(DAT_00917580 + 0x10) = (int)uVar5;
  *(int *)(DAT_00917580 + 0x14) = (int)((ulonglong)uVar5 >> 0x20);
  *(undefined4 *)(DAT_00917580 + 0x18) = 1;
  if (DAT_00915567 == '\0') {
    DAT_009175a0 = ((*(int *)(DAT_00917580 + 0x10) - *(int *)(DAT_00917580 + 8)) + 1) * DAT_00919868
                   >> 0x10;
    DAT_009175a4 = ((*(int *)(DAT_00917580 + 0x14) - *(int *)(DAT_00917580 + 0xc)) + 1) *
                   DAT_0091986c >> 0x10;
  }
  local_c = *(undefined4 *)(&DAT_0260d764 + param_1 * 4);
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_14);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_1c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_0042de50();
    local_10 = *(int **)(*piVar4 + 4);
    (**(code **)(*local_10 + 0x14))(param_2);
    FUN_00438c10(local_18,0);
  }
  return;
}

