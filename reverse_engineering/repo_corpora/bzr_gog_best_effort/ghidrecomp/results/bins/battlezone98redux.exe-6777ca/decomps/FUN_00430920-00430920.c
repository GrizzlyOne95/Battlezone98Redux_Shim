
void FUN_00430920(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_14 [8];
  int local_c;
  undefined1 local_8 [4];
  
  FUN_00428a90();
  FUN_00424640(local_8);
  local_c = 0;
  while( true ) {
    uVar2 = FID_conflict_begin(local_14);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    uVar2 = FUN_00421ea0();
    FUN_00432510(uVar2);
    FUN_00422190();
    local_c = local_c + 1;
  }
  return;
}

