
void FUN_004b1f70(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_1c = FUN_00417c70();
  FUN_00422170();
  local_10 = DAT_00917a74;
  puVar2 = (undefined4 *)FID_conflict_begin(local_20);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_28);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_8 = *piVar4;
    if ((((local_8 != local_1c) &&
         (local_14 = (**(code **)(*(int *)(local_8 + 0x18) + 0x30))(), local_14 != 0)) &&
        ((*(uint *)(local_14 + 0x14) & 0x200) == 0)) &&
       (((local_18 = FUN_00462450(), local_18 < 5 || (8 < local_18)) &&
        (cVar1 = FUN_004b1f30(local_8), cVar1 == '\0')))) {
      (**(code **)(*(int *)(local_8 + 0x18) + 8))(3);
      (**(code **)(*(int *)(local_8 + 0x18) + 0x10))();
      puVar2 = (undefined4 *)FID_conflict_begin(local_2c);
      local_c = *puVar2;
    }
    FUN_0046b260(local_24,0);
  }
  return;
}

