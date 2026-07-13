
void FUN_007d2110(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  int local_8;
  
  if (param_2 == 0) {
    FUN_0041fe40(&param_1);
  }
  else {
    local_8 = 0;
    while (iVar1 = size(), local_8 < iVar1) {
      piVar2 = (int *)FUN_004200d0(local_8);
      if (*piVar2 == param_2) {
        puVar4 = local_14;
        iVar1 = local_8;
        FID_conflict_begin(local_18);
        puVar3 = (undefined4 *)FID_conflict_operator_(puVar4,iVar1);
        local_10 = *puVar3;
        FUN_007c94e0(local_1c,local_10,&param_1);
        return;
      }
      local_8 = local_8 + 1;
    }
  }
  return;
}

