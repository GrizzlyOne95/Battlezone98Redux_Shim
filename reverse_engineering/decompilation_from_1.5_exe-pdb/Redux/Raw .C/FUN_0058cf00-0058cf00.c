
void FUN_0058cf00(int param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  float *local_8;
  
  if ((((-1 < param_1) && (param_1 <= DAT_02a13cb8)) && (-1 < param_2)) &&
     (((param_2 <= DAT_02a13c84 && (DAT_0091814c != 0)) &&
      (local_10 = (char *)((param_1 * DAT_02a13c70 + param_2) * 0x118 + DAT_0091814c),
      *local_10 != '\0')))) {
    local_14 = local_10 + 4;
    FUN_00422170();
    puVar2 = (undefined4 *)FID_conflict_begin(local_1c);
    local_c = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_20);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      puVar2 = (undefined4 *)FUN_00421ec0();
      local_18 = *puVar2;
      FUN_0058c1b0(local_18);
      FUN_0058ca30(local_18);
      FUN_00421ee0();
    }
    FUN_0041ff50();
    local_8 = (float *)FUN_0058c980(1);
    local_8[4] = 9.80909e-45;
    local_8[6] = -NAN;
    *local_8 = (float)(param_2 * 0x10 + DAT_02ce99c0);
    local_8[2] = *local_8 + 16.0;
    local_8[1] = (float)(param_1 * 0x10 + DAT_02cd9984);
    local_8[3] = local_8[1] + 16.0;
    FUN_0041fe40(&local_8);
    *local_10 = '\0';
    FUN_0058be60(local_8);
  }
  return;
}

