
void FUN_004b6660(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int *local_c;
  undefined4 local_8;
  
  DAT_0091756c = 0;
  DAT_00917550 = DAT_0091552c;
  DAT_00917574 = 0x14;
  DAT_00917564 = 0x14;
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_10);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_18);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_0042de50();
    local_c = (int *)*puVar2;
    (**(code **)(*local_c + 4))();
    FUN_00438c10(local_14,0);
  }
  FUN_0062c3c0(FUN_004b6560);
  FUN_0062c3f0(FUN_004b65e0);
  return;
}

