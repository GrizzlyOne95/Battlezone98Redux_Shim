
void FUN_00679830(int param_1)

{
  char cVar1;
  void *pvVar2;
  wchar_t *pwVar3;
  int iVar4;
  undefined4 local_28;
  undefined4 local_20;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f388;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = FUN_0041fc90(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (cVar1 == '\0') {
    pwVar3 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)(local_14 + 0x1b0 + param_1 * 0xc));
    local_18 = *(undefined4 *)pwVar3;
    if (param_1 == 1) {
      iVar4 = __RTDynamicCast(local_18,0,&DynamicGeometryBatch::RTTI_Type_Descriptor,
                              &DynamicGeometryOcclusionQueryBatch::RTTI_Type_Descriptor,0);
      if (iVar4 != 0) {
        *(undefined1 *)(iVar4 + 0xb8) = 0;
      }
    }
    FUN_004cbb80();
  }
  else {
    if (param_1 == 1) {
      pvVar2 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>::operator_new(0xbc);
      local_8 = 1;
      if (pvVar2 == (void *)0x0) {
        local_28 = 0;
      }
      else {
        local_28 = FUN_0067a8c0(local_14);
      }
      local_18 = local_28;
    }
    else {
      pvVar2 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>::operator_new(0xb4);
      local_8 = 0;
      if (pvVar2 == (void *)0x0) {
        local_20 = 0;
      }
      else {
        local_20 = FUN_0067a270(local_14,0);
      }
      local_18 = local_20;
    }
    local_8 = 0xffffffff;
  }
  FUN_0041fe40(&local_18);
  *(undefined4 *)(local_14 + 0x1c8) = local_18;
  DAT_02ceb83c = DAT_02ceb83c + 1;
  ExceptionList = local_10;
  return;
}

