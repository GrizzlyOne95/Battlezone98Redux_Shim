
void FUN_0041b2d0(int param_1)

{
  uint uVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  uint local_8;
  
  local_8 = 0;
  while (uVar1 = size(), local_8 < uVar1) {
    piVar2 = (int *)FUN_004200d0(local_8);
    if (*piVar2 == param_1) {
      puVar4 = local_14;
      uVar1 = local_8;
      FID_conflict_begin(local_18);
      puVar3 = (undefined4 *)FID_conflict_operator_(puVar4,uVar1);
      local_10 = *puVar3;
      FUN_004200f0(local_1c,local_10);
    }
    else {
      local_8 = local_8 + 1;
    }
  }
  FUN_0041ac90(param_1);
  return;
}

