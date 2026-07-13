
void FUN_00477810(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  int *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_1c);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_24);
    cVar1 = FUN_00420f10(uVar3);
    if ((cVar1 == '\0') || (local_10 = (int *)FUN_0042de50(), *local_10 == param_1)) break;
    FUN_00438c10(local_20,0);
  }
  local_14 = local_8;
  FUN_0042d920(local_28,local_8);
  cVar1 = FUN_0042d8f0();
  if (cVar1 != '\0') {
    local_18 = local_c;
    FUN_0045e290(&local_18);
  }
  return;
}

