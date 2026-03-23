
void FUN_00591a70(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  int local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  if (DAT_0091814c != 0) {
    local_c = DAT_02a13c70 * DAT_02a13c9c;
    local_14 = DAT_0091814c;
    while( true ) {
      local_20 = local_c;
      iVar2 = local_c + -1;
      if (local_c == 0) break;
      local_c = iVar2;
      FUN_00422170();
      local_10 = local_14 + 4;
      puVar3 = (undefined4 *)FID_conflict_begin(local_30);
      local_8 = *puVar3;
      while( true ) {
        uVar4 = FID_conflict_end(local_34);
        cVar1 = FID_conflict_operator__(uVar4);
        if (cVar1 == '\0') break;
        puVar3 = (undefined4 *)FUN_00421ec0();
        FUN_0058ca30(*puVar3);
        FUN_00421ee0();
      }
      FUN_0041ff50();
      local_14 = local_14 + 0x118;
    }
    local_24 = DAT_0091814c;
    local_18 = DAT_0091814c;
    if (DAT_0091814c == 0) {
      local_28 = 0;
      local_c = iVar2;
    }
    else {
      local_c = iVar2;
      local_28 = FUN_0058cdf0(3);
    }
    DAT_0091814c = 0;
    DAT_0091819c = DAT_0091819c + DAT_02a13c70 * DAT_02a13c9c * -0x118;
  }
  if (DAT_02a13c8c != 0) {
    local_1c = DAT_02a13c8c;
    DAT_009181a0 = 0;
    FUN_0041ff50();
    FUN_004bae50(0x80000);
  }
  if (DAT_00918138 != 0) {
    local_2c = DAT_00918138;
    operator_delete__((void *)DAT_00918138);
    DAT_00918138 = 0;
    DAT_00918194 = 0;
    DAT_00918190 = 0;
  }
  FUN_0058c220();
  return;
}

