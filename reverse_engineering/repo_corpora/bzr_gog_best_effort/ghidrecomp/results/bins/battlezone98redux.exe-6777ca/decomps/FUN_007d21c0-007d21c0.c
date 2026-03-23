
void FUN_007d21c0(int param_1)

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
  
  local_8 = 0;
  while( true ) {
    iVar1 = size();
    if (iVar1 <= local_8) {
      return;
    }
    piVar2 = (int *)FUN_004200d0(local_8);
    if (*piVar2 == param_1) break;
    local_8 = local_8 + 1;
  }
  puVar4 = local_14;
  iVar1 = local_8;
  FID_conflict_begin(local_18);
  puVar3 = (undefined4 *)FID_conflict_operator_(puVar4,iVar1);
  local_10 = *puVar3;
  FUN_004200f0(local_1c,local_10);
  return;
}

