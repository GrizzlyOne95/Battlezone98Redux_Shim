
int FUN_004cca70(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int *local_c;
  undefined1 local_8 [4];
  
  FUN_0042d8c0(local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_14);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') {
      return 0;
    }
    local_c = (int *)FUN_0042de50();
    local_c = (int *)*local_c;
    if (*local_c == param_1) break;
    FUN_00438c10(local_10,0);
  }
  return local_c[1];
}

