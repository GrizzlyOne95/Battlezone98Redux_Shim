
int FUN_004e4750(undefined4 *param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  float10 fVar5;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  int local_1c;
  float local_18;
  float local_14;
  undefined *local_10;
  undefined4 local_c;
  int local_8;
  
  local_18 = 1e+30;
  local_1c = 0;
  local_10 = &DAT_009b63fc;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_20);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_28);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_8 = *piVar4;
    if ((local_8 != param_2) && (*(char *)(local_8 + 0x239) == '\0')) {
      puVar2 = (undefined4 *)(**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
      fVar5 = (float10)FUN_004620b0(*param_1,param_1[1],param_1[2],*puVar2,puVar2[1],puVar2[2]);
      local_14 = (float)fVar5;
      if (local_14 < local_18) {
        local_1c = local_8;
        local_18 = local_14;
      }
    }
    FUN_0046b260(local_24,0);
  }
  return local_1c;
}

