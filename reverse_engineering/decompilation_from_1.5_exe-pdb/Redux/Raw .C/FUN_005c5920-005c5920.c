
void FUN_005c5920(void)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined1 local_20 [8];
  int local_18;
  float *local_14;
  undefined *local_10;
  int local_c;
  undefined4 local_8;
  
  if (DAT_009180d6 != '\0') {
    FUN_005b2bd0();
    local_10 = &DAT_025cf554;
    FUN_00422170();
    puVar2 = (undefined4 *)FID_conflict_begin();
    local_8 = *puVar2;
    while( true ) {
      FID_conflict_end();
      cVar1 = FID_conflict_operator__();
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_00421ec0();
      local_c = *piVar3;
      local_18 = FUN_00462380();
      if (local_18 != 0) {
        local_14 = (float *)(**(code **)(*(int *)(local_c + 0x18) + 0xc))();
        FUN_005b2c30(local_18,(double)*local_14,(double)local_14[2]);
      }
      FUN_0046b260(local_20,0);
    }
    FUN_00417c60();
    DAT_009180d6 = '\0';
  }
  return;
}

