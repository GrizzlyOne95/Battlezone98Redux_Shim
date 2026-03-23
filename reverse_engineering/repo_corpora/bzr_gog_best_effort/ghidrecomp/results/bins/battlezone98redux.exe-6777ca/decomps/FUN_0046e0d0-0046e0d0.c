
void FUN_0046e0d0(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c [8];
  
  puVar1 = (undefined4 *)FID_conflict_end(local_18);
  local_10 = *puVar1;
  puVar3 = local_c;
  puVar1 = (undefined4 *)FID_conflict_end(local_1c);
  uVar2 = *puVar1;
  puVar1 = (undefined4 *)FID_conflict_begin(local_20);
  puVar1 = (undefined4 *)FUN_0046e930(local_24,*puVar1,uVar2,puVar3);
  local_14 = *puVar1;
  FID_conflict_erase(local_28,local_14,local_10);
  return;
}

