
void __fastcall FUN_005d8e20(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  if (*(int *)(param_1 + 0x10) != 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x24) = 0;
  }
  *(undefined4 *)(param_1 + 0x10) = 0;
  local_c = param_1;
  local_8 = param_1;
  puVar1 = (undefined4 *)FID_conflict_end(local_18);
  local_10 = *puVar1;
  piVar3 = &local_c;
  puVar1 = (undefined4 *)FID_conflict_end(local_1c);
  uVar2 = *puVar1;
  puVar1 = (undefined4 *)FID_conflict_begin(local_20);
  puVar1 = (undefined4 *)FUN_0046e930(local_24,*puVar1,uVar2,piVar3);
  local_14 = *puVar1;
  FID_conflict_erase(local_28,local_14,local_10);
  return;
}

