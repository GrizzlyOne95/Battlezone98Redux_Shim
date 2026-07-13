
void FUN_00626900(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [5];
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  if (DAT_00920174 == 0) {
    if (DAT_00920170 == 0) {
      local_7 = 0;
      uVar2 = 0;
      puVar1 = (undefined4 *)FID_conflict_end(local_1c);
      uVar3 = *puVar1;
      puVar1 = (undefined4 *)FID_conflict_begin(local_20);
      FUN_00627ea0(*puVar1,uVar3,uVar2);
    }
    else {
      local_6 = 0;
      uVar2 = 0;
      puVar1 = (undefined4 *)FID_conflict_end(local_14);
      uVar3 = *puVar1;
      puVar1 = (undefined4 *)FID_conflict_begin(local_18);
      FUN_00627e60(*puVar1,uVar3,uVar2);
    }
  }
  else {
    local_5 = 0;
    uVar2 = 0;
    puVar1 = (undefined4 *)FID_conflict_end(local_c);
    uVar3 = *puVar1;
    puVar1 = (undefined4 *)FID_conflict_begin(local_10);
    FUN_00627e20(*puVar1,uVar3,uVar2);
  }
  return;
}

