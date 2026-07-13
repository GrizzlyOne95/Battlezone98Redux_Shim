
void FUN_00680fe0(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  Root *this;
  Viewport *pVVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  undefined1 uVar6;
  vector<float,class_Ogre::STLAllocator<float,class_Ogre::CategorisedAllocPolicy<0>_>_>
  local_90 [40];
  DefaultShadowCameraSetup *local_68;
  uint local_64;
  PSSMShadowCameraSetup *local_60;
  PSSMShadowCameraSetup *local_5c;
  DefaultShadowCameraSetup *local_58;
  PSSMShadowCameraSetup *local_54;
  DefaultShadowCameraSetup *local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  RenderWindow *local_40;
  PSSMShadowCameraSetup *local_3c;
  byte local_35;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24 [4];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_48 = (uint)*(char *)(DAT_0094672c + 0x25);
  if ((int)local_48 < 0) {
    (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x3c0))(1,1,0x21,0,0);
  }
  else {
    if (4 < local_48) {
      local_48 = 4;
    }
    if (*(char *)((int)&PTR_DAT_008ed0bc + local_48) == '\0') {
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x3c0))
                (*(undefined2 *)(&DAT_008ed0c8 + local_48 * 4),1,0x21,0,1);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x394))(0x43000000);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x3c8))(0x3f4ccccd);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x38c))(0x43400000);
      Ogre::SceneManager::setShadowTextureCountPerLightType
                (*(SceneManager **)(DAT_00920ea0 + 8),1,1);
      local_50 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<3>_>::operator_new(4);
      if (local_50 == (DefaultShadowCameraSetup *)0x0) {
        local_58 = (DefaultShadowCameraSetup *)0x0;
      }
      else {
        Ogre::DefaultShadowCameraSetup::DefaultShadowCameraSetup(local_50);
        *(undefined ***)local_50 = Ogre::DefaultShadowCameraSetup::vftable;
        local_58 = local_50;
      }
      local_68 = local_58;
      uVar3 = FUN_00683d90(local_58,0);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x3f0))(uVar3);
      FUN_004499a0();
    }
    else {
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x3c0))
                (*(undefined2 *)(&DAT_008ed0c8 + local_48 * 4),3,0x21,0,1);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x394))(0x43000000);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x3c8))(0x3f4ccccd);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x38c))(0x43400000);
      Ogre::SceneManager::setShadowTextureCountPerLightType
                (*(SceneManager **)(DAT_00920ea0 + 8),1,3);
      local_54 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<3>_>::operator_new(0xbc);
      if (local_54 == (PSSMShadowCameraSetup *)0x0) {
        local_5c = (PSSMShadowCameraSetup *)0x0;
      }
      else {
        Ogre::PSSMShadowCameraSetup::PSSMShadowCameraSetup(local_54);
        *(undefined ***)local_54 = Ogre::PSSMShadowCameraSetup::vftable;
        local_5c = local_54;
      }
      local_60 = local_5c;
      local_3c = local_5c;
      (**(code **)(*(int *)local_5c + 0x10))(1);
      Ogre::FocusedShadowCameraSetup::setUseAggressiveFocusRegion
                ((FocusedShadowCameraSetup *)local_3c,true);
      puVar2 = (undefined4 *)FUN_0044c7a0(0);
      (**(code **)(*(int *)local_3c + 0x18))(*puVar2);
      local_34 = 0x3dcccccd;
      local_30 = 0x41800000;
      local_2c = 0x42800000;
      local_28 = 0x43800000;
      uVar3 = FUN_00683ab0();
      puVar2 = (undefined4 *)FUN_00416430(&local_34,local_24);
      FUN_00683a00(*puVar2,puVar2[1],uVar3);
      FUN_00683ad0();
      Ogre::PSSMShadowCameraSetup::setSplitPoints(local_3c,local_90);
      Ogre::PSSMShadowCameraSetup::setOptimalAdjustFactor(local_3c,0,0.0);
      Ogre::PSSMShadowCameraSetup::setOptimalAdjustFactor(local_3c,1,0.0);
      Ogre::PSSMShadowCameraSetup::setOptimalAdjustFactor(local_3c,2,0.0);
      uVar3 = FUN_00683d90(local_3c,0);
      (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x3f0))(uVar3);
      FUN_004499a0();
      FUN_00683a90();
    }
  }
  this = Ogre::Root::getSingleton();
  local_40 = Ogre::Root::getAutoCreatedWindow(this);
  if ((local_40 != (RenderWindow *)0x0) &&
     (sVar1 = (**(code **)(*(int *)local_40 + 0x30))(), sVar1 != 0)) {
    local_44 = (uint)*(byte *)(DAT_0094672c + 0x27);
    basic_string<>();
    local_35 = 0;
    if ((int)local_48 < 0) {
      if (local_44 == 0) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_20,"high-noshadow");
      }
      else if (local_44 == 1) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_20,"medium-noshadow");
      }
      else if (local_44 == 2) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_20,"low-noshadow");
      }
      else {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_20,"lowest-noshadow");
      }
    }
    else {
      local_35 = 1;
      if (*(char *)((int)&PTR_DAT_008ed0bc + local_48) == '\0') {
        if (local_44 == 0) {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator=(local_20,"high");
        }
        else if (local_44 == 1) {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator=(local_20,"medium");
        }
        else if (local_44 == 2) {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator=(local_20,"low");
        }
        else {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator=(local_20,"lowest");
        }
      }
      else if (local_44 == 0) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_20,"high-pssm");
      }
      else if (local_44 == 1) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_20,"medium-pssm");
      }
      else if (local_44 == 2) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_20,"low-pssm");
      }
      else {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_20,"lowest-pssm");
      }
    }
    local_64 = (**(code **)(*(int *)local_40 + 0x30))();
    local_64 = local_64 & 0xffff;
    for (local_4c = 0; (int)local_4c < (int)local_64; local_4c = local_4c + 1) {
      pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (uint)local_35;
      uVar6 = (undefined1)local_4c;
      pVVar4 = (Viewport *)(**(code **)(*(int *)local_40 + 0x34))();
      Ogre::Viewport::setShadowsEnabled(pVVar4,(bool)uVar6);
      pVVar4 = (Viewport *)(**(code **)(*(int *)local_40 + 0x34))(local_4c & 0xffff,local_20);
      Ogre::Viewport::setMaterialScheme(pVVar4,pbVar5);
    }
    ~basic_string<>();
  }
  FUN_0083e885();
  return;
}

