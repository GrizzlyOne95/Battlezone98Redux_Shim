
undefined4 * FUN_005d8770(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined4 **ppuVar6;
  undefined8 uVar5;
  undefined1 local_30 [8];
  undefined1 local_28 [8];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c2f8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0047e9c0(param_1,param_2);
  local_8 = 0;
  *local_14 = SpawnBuoy::vftable;
  local_14[6] = SpawnBuoy::vftable;
  FUN_00442d30();
  local_14[0x8e] = 0;
  cVar1 = FUN_00571c40(uVar2);
  if (cVar1 != '\0') {
    FUN_0062de40(local_14[0x3d],1);
    *(uint *)(local_14[0x3d] + 0x14) = *(uint *)(local_14[0x3d] + 0x14) | 0x400;
    *(undefined4 *)(local_14[0x3d] + 0xd0) = 0x3f800000;
    local_18 = local_14;
    puVar3 = (undefined4 *)FID_conflict_end();
    local_1c = *puVar3;
    ppuVar6 = &local_18;
    puVar3 = (undefined4 *)FID_conflict_end(local_28);
    uVar5 = CONCAT44(ppuVar6,*puVar3);
    puVar3 = (undefined4 *)FID_conflict_begin();
    puVar3 = (undefined4 *)FUN_0046e930(local_30,*puVar3,uVar5);
    local_20 = *puVar3;
    FID_conflict_erase();
  }
  if (*(int *)(param_1 + 0x78) == 0) {
    fVar4 = (float10)FUN_007855e0(*(undefined8 *)(local_14[0x3d] + 0x48),
                                  *(undefined8 *)(local_14[0x3d] + 0x58));
    *(double *)(local_14[0x3d] + 0x50) = (double)fVar4;
    FUN_004db100();
  }
  ExceptionList = local_10;
  return local_14;
}

