
void FUN_005d3100(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined1 local_5;
  
  FUN_00422170();
  local_5 = 0;
  puVar2 = (undefined4 *)FUN_00424640(local_10);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_14);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') {
      return;
    }
    piVar4 = (int *)FUN_004237d0();
    if (*piVar4 == param_1) break;
    FUN_00422190();
  }
  puVar2 = (undefined4 *)FUN_004237d0();
  local_28 = *puVar2;
  local_24 = puVar2[1];
  local_20 = puVar2[2];
  FUN_0045e7a0(local_18,local_c);
  local_24 = param_2;
  FUN_005d3250(local_1c,&local_28);
  return;
}

