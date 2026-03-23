
void FUN_004b6b80(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [8];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = *(undefined4 *)(&DAT_0260d764 + param_1 * 4);
  puVar1 = (undefined4 *)FID_conflict_begin(local_18);
  local_10 = *puVar1;
  puVar1 = (undefined4 *)FUN_00447eb0(local_c);
  uVar3 = *puVar1;
  puVar1 = (undefined4 *)FID_conflict_begin(local_20);
  uVar2 = *puVar1;
  puVar1 = (undefined4 *)FUN_0042d8c0(local_24);
  puVar1 = (undefined4 *)FUN_004b72e0(local_28,*puVar1,uVar2,uVar3);
  local_14 = *puVar1;
  FUN_0042d970(local_2c,local_14,local_10);
  return;
}

