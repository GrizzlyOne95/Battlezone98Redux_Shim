
uint FUN_006bb9a0(void)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  QuickBitSet local_14 [8];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  Concurrency::details::QuickBitSet::QuickBitSet(local_14);
  puVar1 = (undefined4 *)FUN_004fee40(local_8);
  uVar3 = *puVar1;
  puVar1 = (undefined4 *)FID_conflict_begin(local_c);
  uVar2 = FUN_006da5b0(*puVar1,uVar3);
  if ((uVar2 & 0xff) == 0) {
    uVar2 = uVar2 & 0xffffff00;
  }
  else {
    uVar2 = FUN_004c85a0();
  }
  return uVar2;
}

