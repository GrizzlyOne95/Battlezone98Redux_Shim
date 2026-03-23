
void FUN_00667e40(void)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined1 local_14 [4];
  undefined4 local_10 [2];
  undefined4 local_8;
  
  FUN_00420260(local_10);
  FID_conflict_begin(local_14);
  local_8 = local_10[0];
  while (cVar1 = FUN_00420f10(local_14), cVar1 != '\0') {
    piVar2 = (int *)FUN_00422150();
    if (*piVar2 == -1) {
      FUN_00428570();
    }
    else {
      puVar3 = (undefined4 *)FUN_004305b0(local_1c,0);
      local_18 = *puVar3;
      FUN_0066a560(local_20,local_18);
    }
  }
  return;
}

