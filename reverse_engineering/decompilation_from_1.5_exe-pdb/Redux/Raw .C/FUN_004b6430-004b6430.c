
void __fastcall FUN_004b6430(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [8];
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [8];
  undefined1 local_28 [4];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  int local_c;
  undefined4 local_8;
  
  *param_1 = DisplayInterface::vftable;
  local_14 = param_1;
  local_10 = param_1;
  FUN_0045e290(&local_14);
  for (local_c = 0; local_c < 0xd; local_c = local_c + 1) {
    local_8 = *(undefined4 *)(&DAT_0260d764 + local_c * 4);
    puVar1 = (undefined4 *)FID_conflict_begin(local_28);
    local_18 = *puVar1;
    puVar1 = (undefined4 *)FUN_00447eb0(local_10);
    uVar3 = *puVar1;
    puVar1 = (undefined4 *)FID_conflict_begin(local_30);
    uVar2 = *puVar1;
    puVar1 = (undefined4 *)FUN_0042d8c0(local_34);
    puVar1 = (undefined4 *)FUN_004b72e0(local_38,*puVar1,uVar2,uVar3);
    local_1c = *puVar1;
    FUN_0042d970(local_3c,local_1c,local_18);
    local_8 = *(undefined4 *)(&DAT_0260d79c + local_c * 4);
    puVar1 = (undefined4 *)FID_conflict_begin(local_40);
    local_20 = *puVar1;
    puVar1 = (undefined4 *)FUN_00447eb0(local_10);
    uVar3 = *puVar1;
    puVar1 = (undefined4 *)FID_conflict_begin(local_48);
    uVar2 = *puVar1;
    puVar1 = (undefined4 *)FUN_0042d8c0(local_4c);
    puVar1 = (undefined4 *)FUN_004b72e0(local_50,*puVar1,uVar2,uVar3);
    local_24 = *puVar1;
    FUN_0042d970(local_54,local_24,local_20);
  }
  return;
}

