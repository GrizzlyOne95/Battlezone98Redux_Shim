
void FUN_00584530(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  
  FUN_00430590();
  if (param_1 == 1) {
    puVar2 = (undefined4 *)FUN_0042d8c0(local_c);
    local_8 = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_begin(local_10);
      cVar1 = FUN_00420f10(uVar3);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_0042de50();
      if (*(int *)(*piVar4 + 0x80) == 2) {
        piVar4 = (int *)FUN_0042de50();
        *(undefined4 *)(*piVar4 + 0x80) = 0;
      }
      FUN_00438c10(local_14,0);
    }
  }
  else {
    puVar2 = (undefined4 *)FUN_0042d8c0(local_18);
    local_8 = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_begin(local_1c);
      cVar1 = FUN_00420f10(uVar3);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_0042de50();
      if (*(int *)(*piVar4 + 0x80) == 2) {
        piVar4 = (int *)FUN_0042de50();
        *(undefined4 *)(*piVar4 + 0x80) = 1;
      }
      FUN_00438c10(local_20,0);
    }
  }
  return;
}

