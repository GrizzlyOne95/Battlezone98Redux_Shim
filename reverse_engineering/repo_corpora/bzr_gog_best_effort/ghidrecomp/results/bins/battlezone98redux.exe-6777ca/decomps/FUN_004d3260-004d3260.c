
void FUN_004d3260(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_20;
  undefined1 local_1c;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int local_10;
  undefined1 local_8 [4];
  
  FUN_0042d8c0(local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_18);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    local_10 = FUN_0042de50();
    *(undefined1 *)(local_10 + 4) = 1;
    FUN_00438c10(local_14,0);
  }
  local_20 = param_1;
  local_1c = 1;
  FUN_00477a70(&local_20);
  return;
}

