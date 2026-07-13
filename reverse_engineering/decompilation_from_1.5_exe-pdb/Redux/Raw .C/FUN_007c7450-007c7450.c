
void FUN_007c7450(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_3c0 [476];
  int local_1e4;
  undefined4 local_1e0 [118];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1e4 = FUN_00417780(&DAT_02cecee0);
  if (((local_1e4 != 0) && (*(int *)(local_1e4 + 8) < *(int *)(local_1e4 + 0x10))) &&
     (*(int *)(local_1e4 + 0xc) < *(int *)(local_1e4 + 0x14))) {
    puVar1 = (undefined4 *)
             FUN_00688370(local_3c0,local_1e4,0x3fb2b8c2,0x3f800000,0x43960000,0x3f800000);
    puVar3 = local_1e0;
    for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_1e0;
    puVar3 = &DAT_008eaae0;
    for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    DAT_008eaad8 = 0xc;
    DAT_008eaad0 = std::
                   _Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>;
    Ogre::Viewport::setVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x1c),0x10);
  }
  FUN_0083e885();
  return;
}

