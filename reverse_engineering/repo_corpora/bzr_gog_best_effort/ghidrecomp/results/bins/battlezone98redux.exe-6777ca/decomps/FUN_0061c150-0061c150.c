
void FUN_0061c150(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  bool bVar5;
  undefined4 local_240 [142];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_00439e60();
  if (DAT_009454b8 != 0) {
    bVar5 = DAT_008eaad8 == 0xc;
    if (bVar5) {
      puVar3 = &DAT_008eaad0;
      puVar4 = local_240;
      for (iVar2 = 0x8e; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      FUN_0061a080();
    }
    DAT_008ead0c = 0;
    DAT_008eaab0 = 1;
    DAT_008eaad4 = 0;
    DAT_008eaad8 = 9;
    DAT_008eaad0 = std::
                   _Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>;
    DAT_008eacb8 = param_1;
    FUN_006885c0(uVar1,0x3f800000);
    FUN_005b0900(0);
    if (bVar5) {
      FUN_0061a000();
      puVar3 = local_240;
      puVar4 = &DAT_008eaad0;
      for (iVar2 = 0x8e; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
    }
  }
  FUN_0083e885();
  return;
}

