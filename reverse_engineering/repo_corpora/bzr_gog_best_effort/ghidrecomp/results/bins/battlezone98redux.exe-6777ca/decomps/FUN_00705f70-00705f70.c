
void FUN_00705f70(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  uVar5 = 0;
  puVar4 = &stack0x0000000c;
  puVar1 = (undefined4 *)FID_conflict_begin(local_c);
  uVar3 = *puVar1;
  puVar1 = (undefined4 *)FUN_004fee40(local_10);
  uVar2 = *puVar1;
  puVar1 = (undefined4 *)FID_conflict_begin(local_14);
  FUN_0070f910(*puVar1,uVar2,uVar3,puVar4,uVar5);
  return;
}

