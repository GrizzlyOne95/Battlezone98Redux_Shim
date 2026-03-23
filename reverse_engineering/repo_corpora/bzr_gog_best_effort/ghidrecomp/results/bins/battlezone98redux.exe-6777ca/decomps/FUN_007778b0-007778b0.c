
void __thiscall
FUN_007778b0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  uint uVar1;
  MeshManager *this;
  undefined4 uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  ManualResourceLoader *pMVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_13c [8];
  undefined4 local_134;
  undefined4 local_130;
  SharedPtr<class_Ogre::Material> *local_12c;
  int *local_128;
  int *local_124;
  int local_120;
  int local_11c;
  int local_118;
  int local_114;
  int local_110;
  ManualResourceLoader local_10c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_f4 [24];
  char local_dc [200];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e367;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_110 = param_1;
  local_14 = uVar1;
  FUN_0083ead2(param_1,8,0x10,Concurrency::details::QuickBitSet::QuickBitSet,FUN_004499a0);
  local_8 = 0;
  *(undefined4 *)(local_110 + 0x240) = param_2;
  *(undefined4 *)(local_110 + 0x244) = param_3;
  *(undefined4 *)(local_110 + 0x248) = param_4;
  *(undefined4 *)(local_110 + 0x24c) = param_5;
  _vector_constructor_iterator_((void *)(local_110 + 0x280),0x10,0x10,FUN_00777620);
  FUN_00777620(uVar1);
  for (local_11c = 0; local_11c < 4; local_11c = local_11c + 1) {
    for (local_120 = 0; local_120 < 4; local_120 = local_120 + 1) {
      *(undefined4 *)(local_110 + 0x80 + local_11c * 0x10 + local_120 * 4) = 0;
      *(undefined4 *)(local_110 + 0xc0 + local_11c * 0x10 + local_120 * 4) = 0;
    }
  }
  FUN_0077c670();
  local_12c = (SharedPtr<class_Ogre::Material> *)FUN_006b6010();
  for (local_118 = 0; local_118 < 4; local_118 = local_118 + 1) {
    for (local_114 = 0; local_114 < 4; local_114 = local_114 + 1) {
      *(undefined1 *)(local_110 + 0x260 + local_118 * 4 + local_114) = 0;
      *(undefined1 *)(local_110 + 0x250 + local_118 * 4 + local_114) = 0;
      *(undefined1 *)(local_110 + 0x270 + local_118 * 4 + local_114) = 0;
      _snprintf(local_dc,200,"RenderableTileCluster_%dx%d_%dx%d",*(undefined4 *)(local_110 + 0x240),
                *(undefined4 *)(local_110 + 0x244),local_118,local_114);
      basic_string<>(local_dc);
      local_8._0_1_ = 1;
      basic_string<>("General");
      local_8._0_1_ = 2;
      pMVar5 = local_10c;
      pbVar4 = local_f4;
      pbVar3 = local_13c;
      this = Ogre::MeshManager::getSingleton();
      local_134 = Ogre::MeshManager::createManual(this,pbVar3,pbVar4,pMVar5);
      local_8._0_1_ = 3;
      local_130 = local_134;
      FUN_00449910(local_134);
      local_8._0_1_ = 2;
      FUN_004499a0();
      local_8._0_1_ = 1;
      ~basic_string<>();
      FUN_007789a0(local_118 * 0x20 + local_110 + local_114 * 8,local_118,local_114);
      local_128 = (int *)get();
      (**(code **)(*local_128 + 0x38))(0);
      uVar2 = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x180))
                        (local_f4,local_118 * 0x20 + local_110 + local_114 * 8);
      *(undefined4 *)(local_110 + 0xc0 + local_118 * 0x10 + local_114 * 4) = uVar2;
      (**(code **)(**(int **)(local_110 + 0xc0 + local_118 * 0x10 + local_114 * 4) + 0xa8))(0x28);
      Ogre::Entity::setMaterial
                (*(Entity **)(local_110 + 0xc0 + local_118 * 0x10 + local_114 * 4),local_12c);
      Ogre::MovableObject::setCastShadows
                (*(MovableObject **)(local_110 + 0xc0 + local_118 * 0x10 + local_114 * 4),false);
      local_124 = (int *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))();
      uVar2 = (**(code **)(*local_124 + 0x180))(ZERO_exref,IDENTITY_exref);
      *(undefined4 *)(local_110 + 0x80 + local_118 * 0x10 + local_114 * 4) = uVar2;
      (**(code **)(**(int **)(local_110 + 0x80 + local_118 * 0x10 + local_114 * 4) + 0x2c))
                (*(undefined4 *)(local_110 + 0x100 + local_118 * 0x30 + local_114 * 0xc),
                 *(undefined4 *)(local_110 + local_118 * 0x30 + 0x104 + local_114 * 0xc),
                 *(undefined4 *)(local_110 + local_118 * 0x30 + 0x108 + local_114 * 0xc));
      (**(code **)(**(int **)(local_110 + 0x80 + local_118 * 0x10 + local_114 * 4) + 0x124))
                (*(undefined4 *)(local_110 + 0xc0 + local_118 * 0x10 + local_114 * 4));
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
    }
  }
  FUN_007787d0();
  FUN_0077c670();
  FUN_0077bfe0();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

