
void FUN_004d32e0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [8];
  int local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  int *local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_2c);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_34);
    cVar1 = FUN_00420f10(uVar3);
    if ((cVar1 == '\0') || (local_14 = (int *)FUN_0042de50(), *local_14 == param_1)) break;
    FUN_00438c10(local_30,0);
  }
  local_18 = local_8;
  FUN_0042d920(local_38,local_8);
  puVar2 = (undefined4 *)FUN_0042d8c0(local_3c);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_44);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    local_1c = FUN_0042de50();
    *(undefined1 *)(local_1c + 4) = 1;
    FUN_00438c10(local_40,0);
  }
  cVar1 = FUN_0042d8f0();
  if (cVar1 != '\0') {
    local_20 = local_c;
    FUN_0045e290(&local_20);
    local_24 = local_c;
    local_10 = local_c;
    if (local_c != 0) {
      FUN_004d3420(1);
    }
  }
  return;
}

