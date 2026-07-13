
void FUN_006b64c0(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [11];
  byte local_5;
  
  uVar1 = (uint)local_5;
  puVar2 = (undefined4 *)FUN_004fee40(local_10);
  uVar5 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_14);
  uVar4 = *puVar2;
  puVar2 = (undefined4 *)FUN_004fee40(local_18);
  uVar3 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_1c);
  FUN_006d9a40(*puVar2,uVar3,uVar4,uVar5,uVar1);
  return;
}

