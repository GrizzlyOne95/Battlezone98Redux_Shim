
void FUN_004d4350(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_005e09e0();
  FUN_00422170();
  local_8 = DAT_00917a68;
  uVar4 = (uint)DAT_0260db1a;
  puVar2 = (undefined4 *)FID_conflict_end(local_14);
  uVar3 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_18);
  FUN_004d4c00(*puVar2,uVar3,uVar4);
  puVar2 = (undefined4 *)FID_conflict_begin(local_1c);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_24);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00421ec0();
    local_10 = (int *)*puVar2;
    (**(code **)(*local_10 + 8))();
    FUN_0046b260(local_20,0);
  }
  FUN_0062c3c0(FUN_004d4250);
  FUN_0062c3f0(FUN_004d42d0);
  return;
}

