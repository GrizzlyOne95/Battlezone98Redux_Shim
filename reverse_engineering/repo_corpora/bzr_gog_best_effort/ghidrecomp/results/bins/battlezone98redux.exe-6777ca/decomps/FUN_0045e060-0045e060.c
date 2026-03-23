
void FUN_0045e060(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  undefined4 local_8;
  
  if (DAT_00915694 != 0) {
    FUN_00430590();
    FID_conflict_begin(local_10);
    puVar2 = (undefined4 *)FUN_0042d8c0(local_14);
    local_8 = *puVar2;
    while (cVar1 = FUN_00420f10(local_10), cVar1 != '\0') {
      piVar3 = (int *)FUN_0042de50();
      local_c = *piVar3;
      if (*(int *)(local_c + 0x10) == param_1) {
        *(undefined4 *)(local_c + 0x10) = 0;
      }
      FUN_00438c10(local_18,0);
    }
  }
  return;
}

