
void FUN_006be370(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_10 [4];
  int local_c;
  undefined1 local_8 [4];
  
  local_c = 0;
  FUN_00420260(local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_10);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    iVar3 = FUN_00422150();
    local_c = local_c + *(int *)(iVar3 + 0x10);
    FUN_00428570();
  }
  iVar3 = local_c;
  FUN_00764760(local_c);
  FUN_00740e50(iVar3);
  return;
}

