
void FUN_00611270(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined *local_10;
  int *local_c;
  undefined4 local_8;
  
  local_10 = &DAT_025f7df8;
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_14);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_1c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    local_c = (int *)FUN_0042de50();
    local_c = (int *)*local_c;
    if (*(short *)(local_c[4] + 0x10) == 0) {
      (**(code **)(*local_c + 0x18))(param_1);
    }
    FUN_00438c10(local_18,0);
  }
  return;
}

