
void FUN_004dfbf0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined *local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  FUN_005c19d0();
  local_14 = &DAT_025ceedc;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_24);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_2c);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    FUN_00421ec0();
    FUN_005c1b30();
    FUN_0046b260(local_28,0);
  }
  fVar6 = (float10)FUN_00822d60();
  local_1c = (float)fVar6;
  local_20 = FUN_00461430();
  local_18 = DAT_00917a74;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_30);
  local_10 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_38);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_8 = *piVar4;
    iVar5 = (**(code **)(*(int *)(local_8 + 0x18) + 4))();
    if (iVar5 < 0) {
      *(undefined4 *)(local_8 + 0xe8) = 0;
    }
    else {
      FUN_004db800();
      cVar1 = FUN_004625d0(local_20);
      if (cVar1 == '\0') {
        if (*(float *)(local_8 + 0xe8) < local_1c) {
          *(undefined4 *)(local_8 + 0xe8) = 0;
        }
        else {
          *(float *)(local_8 + 0xe8) = *(float *)(local_8 + 0xe8) - local_1c;
        }
      }
      else {
        *(undefined4 *)(local_8 + 0xe8) = 0x3f800000;
      }
    }
    FUN_0046b260(local_34,0);
  }
  return;
}

