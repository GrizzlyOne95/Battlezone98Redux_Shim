
void FUN_005caa20(float param_1,float *param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  float10 fVar4;
  undefined1 local_60 [56];
  undefined1 local_28 [4];
  float local_24;
  undefined4 *local_20;
  int local_1c;
  undefined1 local_18 [4];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c7a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_005c5920(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_005b28e0((double)*param_2,(double)param_2[2],(double)param_1,local_60);
  vector<>();
  local_8 = 0;
  FUN_004bae50(0x40);
  while (cVar1 = FUN_00462710(&local_20), cVar1 != '\0') {
    local_14 = FUN_004da060(*local_20);
    if (local_14 != 0) {
      (**(code **)(*(int *)(local_14 + 0x18) + 0xc))();
      fVar4 = (float10)FUN_00462010();
      local_24 = (float)fVar4;
      if (local_24 < param_1 * param_1) {
        FUN_0041fe40(&local_14);
      }
    }
  }
  FID_conflict_begin(local_18);
  while( true ) {
    uVar2 = FID_conflict_end(local_28);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_00421ec0();
    local_1c = *piVar3;
    (**(code **)(*(int *)(local_1c + 0x18) + 0x10))();
    FUN_00421ee0();
  }
  local_8 = 0xffffffff;
  FUN_0041fe20();
  ExceptionList = local_10;
  return;
}

