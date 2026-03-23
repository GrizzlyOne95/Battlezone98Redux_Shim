
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006a3e20(void)

{
  int iVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  int local_1c;
  int *local_18;
  undefined *local_14;
  undefined *local_10;
  int local_c;
  undefined4 local_8;
  
  local_10 = &DAT_0260af90;
  local_14 = &DAT_0260afd0;
  DAT_02c00abc = size();
  for (local_c = 0; local_c < DAT_02c00abc; local_c = local_c + 1) {
    puVar3 = (undefined4 *)FUN_004200d0(local_c);
    local_18 = (int *)FUN_006a0a20(*(undefined4 *)*puVar3);
    *local_18 = local_c;
  }
  local_1c = FUN_006a0a20(DAT_02c00edc);
  _DAT_02c00a90 = (uint)*(ushort *)(local_1c + 0x5a);
  FUN_00422170();
  puVar3 = (undefined4 *)FID_conflict_begin(local_20);
  local_8 = *puVar3;
  while( true ) {
    uVar4 = FID_conflict_end(local_28);
    cVar2 = FID_conflict_operator__(uVar4);
    if (cVar2 == '\0') break;
    piVar5 = (int *)FUN_00421ec0();
    uVar4 = *(undefined4 *)*piVar5;
    iVar1 = ((undefined4 *)*piVar5)[1];
    if (iVar1 != 0) {
      uVar6 = FUN_006a3d50(iVar1);
      FUN_006a3db0(uVar4,uVar6);
    }
    FUN_0046b260(local_24,0);
  }
  puVar3 = (undefined4 *)FID_conflict_begin(local_2c);
  local_8 = *puVar3;
  while( true ) {
    uVar4 = FID_conflict_end(local_34);
    cVar2 = FID_conflict_operator__(uVar4);
    if (cVar2 == '\0') break;
    piVar5 = (int *)FUN_00421ec0();
    uVar4 = *(undefined4 *)*piVar5;
    iVar1 = ((undefined4 *)*piVar5)[1];
    if (iVar1 != 0) {
      uVar6 = FUN_006a3d50(iVar1,uVar4);
      FUN_006a3db0(uVar4,uVar6);
    }
    FUN_0046b260(local_30,0);
  }
  return;
}

