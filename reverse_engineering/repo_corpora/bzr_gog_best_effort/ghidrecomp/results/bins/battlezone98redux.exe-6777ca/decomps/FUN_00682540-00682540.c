
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00682540(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  float *pfVar4;
  Quaternion *pQVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  undefined4 uVar9;
  uint uStack_39c;
  undefined1 local_38c [64];
  undefined1 local_34c [64];
  undefined1 local_30c [64];
  Quaternion local_2cc [16];
  undefined1 local_2bc [16];
  Quaternion local_2ac [16];
  Quaternion local_29c [16];
  undefined1 local_28c [16];
  undefined1 local_27c [16];
  undefined1 local_26c [4];
  undefined1 local_268 [4];
  undefined1 local_264 [4];
  undefined1 local_260 [4];
  undefined1 local_25c [4];
  undefined1 local_258 [8];
  ulong local_250;
  float local_24c;
  float local_248;
  float local_244;
  float local_240;
  char local_239;
  int local_238;
  char local_231;
  undefined4 *local_230;
  int local_22c;
  float local_228;
  float local_224;
  float local_220;
  float local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  float local_208;
  float local_204;
  float local_200;
  float local_1fc;
  undefined4 local_1f8 [16];
  undefined4 local_1b8 [16];
  undefined4 local_178 [16];
  undefined4 local_138 [16];
  undefined4 local_f8 [16];
  undefined4 local_b8 [16];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_78 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_60 [24];
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f81e;
  local_10 = ExceptionList;
  uStack_39c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_39c;
  ExceptionList = &local_10;
  local_18 = uStack_39c;
  iVar2 = FUN_00684ca0(1);
  if (iVar2 == 0) {
    iVar2 = FUN_00572a70();
    if (iVar2 == 0) {
      FUN_00822ed0(100);
    }
    else {
      FUN_00822ed0(1);
    }
  }
  else {
    DAT_00920c6f = 0;
    FUN_00687d80();
    if ((DAT_02cc3388 & 1) == 0) {
      DAT_02cc3388 = DAT_02cc3388 | 1;
      local_8 = 0;
      Ogre::Vector3::Vector3((Vector3 *)&DAT_02cc3378);
      local_8 = 0xffffffff;
    }
    if ((DAT_0091815b != '\0') && (DAT_00920ca0 == 0)) {
      FUN_0067df70();
    }
    local_250 = Ogre::Timer::getMillisecondsCPU(*(Timer **)(DAT_00920ea0 + 0x2c));
    DAT_00920ea8 = (double)(int)local_250 + (double)(&DAT_008a2fd0)[-((int)local_250 >> 0x1f)];
    cVar1 = (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x88))();
    if (cVar1 == '\0') {
      iVar2 = FUN_00572a70();
      if (iVar2 == 0) {
        FUN_00822ed0(100);
      }
      else {
        FUN_00822ed0(1);
      }
    }
    else {
      if ((DAT_008eaaa4 != 0) || (200.0 < DAT_00920ea8 - _DAT_02cc2c10)) {
        _DAT_02cc2c10 = DAT_00920ea8;
        local_230 = (undefined4 *)FUN_00439e60();
        cVar1 = FUN_005ddde0();
        if ((cVar1 == '\0') || (cVar1 = FUN_005cd290(), cVar1 != '\0')) {
          if (*(int *)(DAT_00920ea0 + 0x20) != 0) {
            iVar2 = Ogre::Viewport::getZOrder(*(Viewport **)(DAT_00920ea0 + 0x20));
            (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x40))(iVar2);
            *(undefined4 *)(DAT_00920ea0 + 0x20) = 0;
          }
        }
        else {
          local_22c = FUN_005dddd0();
          uVar9 = 0x40000000;
          puVar8 = local_260;
          Ogre::Math::ATan((float)local_258);
          uVar9 = FUN_00662dc0(puVar8,uVar9);
          (**(code **)(**(int **)(DAT_00920ea0 + 0x14) + 0x138))(uVar9);
          (**(code **)(**(int **)(DAT_00920ea0 + 0x14) + 0x148))((float)local_230[4] * 0.5);
          Ogre::Camera::setPosition
                    (*(Camera **)(DAT_00920ea0 + 0x14),
                     (float)(*(double *)(local_22c + 0x160) - (double)_DAT_025f8e4c),
                     (float)(*(double *)(local_22c + 0x168) - (double)_DAT_025f8e50),
                     (float)(-*(double *)(local_22c + 0x170) - (double)_DAT_025f8e54));
          puVar3 = (undefined4 *)FUN_008203f0(local_30c,local_22c + 0x40);
          puVar7 = local_138;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar7 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar7 = puVar7 + 1;
          }
          puVar3 = local_138;
          puVar7 = local_b8;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar7 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar7 = puVar7 + 1;
          }
          pfVar4 = (float *)FUN_0081f1e0(local_28c,local_b8);
          local_218 = *pfVar4;
          local_214 = pfVar4[1];
          local_210 = pfVar4[2];
          local_20c = pfVar4[3];
          local_48 = local_218;
          local_44 = local_214;
          local_40 = local_210;
          local_3c = local_20c;
          pQVar5 = (Quaternion *)
                   Ogre::Quaternion::Quaternion(local_2cc,local_20c,local_218,local_214,-local_210);
          Ogre::Camera::setOrientation(*(Camera **)(DAT_00920ea0 + 0x14),pQVar5);
          iVar2 = Ogre::Viewport::getActualWidth(*(Viewport **)(DAT_00920ea0 + 0x1c));
          local_24c = *(float *)(local_22c + 0x14) / (float)iVar2;
          iVar2 = Ogre::Viewport::getActualHeight(*(Viewport **)(DAT_00920ea0 + 0x1c));
          local_244 = *(float *)(local_22c + 0x18) / (float)iVar2 + 0.013;
          iVar2 = Ogre::Viewport::getActualWidth(*(Viewport **)(DAT_00920ea0 + 0x1c));
          local_248 = ((*(float *)(local_22c + 0x1c) - *(float *)(local_22c + 0x14)) + 1.0) /
                      (float)iVar2;
          iVar2 = Ogre::Viewport::getActualHeight(*(Viewport **)(DAT_00920ea0 + 0x1c));
          DAT_00920ebc = ((*(float *)(local_22c + 0x20) - *(float *)(local_22c + 0x18)) + 1.0) /
                         (float)iVar2;
          DAT_00920ec8 = local_24c;
          DAT_00920eb8 = local_244;
          DAT_00920ec4 = local_248;
          local_240 = DAT_00920ebc;
          if (*(int *)(DAT_00920ea0 + 0x20) == 0) {
            uVar9 = (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x2c))
                              (*(undefined4 *)(DAT_00920ea0 + 0x14),2,local_24c,local_244,local_248,
                               DAT_00920ebc);
            *(undefined4 *)(DAT_00920ea0 + 0x20) = uVar9;
            Ogre::Viewport::setVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x20),2);
            Ogre::Viewport::setClearEveryFrame(*(Viewport **)(DAT_00920ea0 + 0x20),true,2);
            Ogre::Viewport::setShadowsEnabled(*(Viewport **)(DAT_00920ea0 + 0x20),false);
            basic_string<>("low-noshadow");
            local_8 = 1;
            Ogre::Viewport::setMaterialScheme(*(Viewport **)(DAT_00920ea0 + 0x20),local_78);
            local_8 = 0xffffffff;
            ~basic_string<>();
          }
          else {
            Ogre::Viewport::setDimensions
                      (*(Viewport **)(DAT_00920ea0 + 0x20),local_24c,local_244,local_248,
                       DAT_00920ebc);
            Ogre::Viewport::setShadowsEnabled(*(Viewport **)(DAT_00920ea0 + 0x20),false);
          }
        }
        iVar2 = FUN_0062c840();
        if ((iVar2 == 0) || (iVar2 = ___scrt_is_user_matherr_present(), iVar2 != 0)) {
          local_231 = '\0';
        }
        else {
          local_231 = '\x01';
        }
        local_239 = local_231;
        cVar1 = FUN_005d6520();
        if ((cVar1 == '\0') || (local_239 == '\0')) {
          if (*(int *)(DAT_00920ea0 + 0x24) != 0) {
            iVar2 = Ogre::Viewport::getZOrder(*(Viewport **)(DAT_00920ea0 + 0x24));
            (**(code **)(*DAT_00920e80 + 0x40))(iVar2);
            *(undefined4 *)(DAT_00920ea0 + 0x24) = 0;
          }
        }
        else {
          local_238 = FUN_005d6510();
          uVar9 = 0x40000000;
          puVar8 = local_264;
          Ogre::Math::ATan((float)local_26c);
          uVar9 = FUN_00662dc0(puVar8,uVar9);
          (**(code **)(**(int **)(DAT_00920ea0 + 0x18) + 0x138))(uVar9);
          (**(code **)(**(int **)(DAT_00920ea0 + 0x18) + 0x148))(*(undefined4 *)(local_238 + 0x10));
          Ogre::Camera::setPosition
                    (*(Camera **)(DAT_00920ea0 + 0x18),
                     (float)(*(double *)(local_238 + 0x160) - (double)_DAT_025f8e4c),
                     (float)(*(double *)(local_238 + 0x168) - (double)_DAT_025f8e50),
                     (float)(-*(double *)(local_238 + 0x170) - (double)_DAT_025f8e54));
          puVar3 = (undefined4 *)FUN_008203f0(local_34c,local_238 + 0x40);
          puVar7 = local_f8;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar7 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar7 = puVar7 + 1;
          }
          puVar3 = local_f8;
          puVar7 = local_178;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar7 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar7 = puVar7 + 1;
          }
          pfVar4 = (float *)FUN_0081f1e0(local_27c,local_178);
          local_208 = *pfVar4;
          local_204 = pfVar4[1];
          local_200 = pfVar4[2];
          local_1fc = pfVar4[3];
          local_28 = local_208;
          local_24 = local_204;
          local_20 = local_200;
          local_1c = local_1fc;
          pQVar5 = (Quaternion *)
                   Ogre::Quaternion::Quaternion(local_29c,local_1fc,local_208,local_204,-local_200);
          Ogre::Camera::setOrientation(*(Camera **)(DAT_00920ea0 + 0x18),pQVar5);
          if (*(int *)(DAT_00920ea0 + 0x24) == 0) {
            uVar9 = (**(code **)(*DAT_00920e80 + 0x2c))
                              (*(undefined4 *)(DAT_00920ea0 + 0x18),0,0,0,0x3f800000,0x3f800000);
            *(undefined4 *)(DAT_00920ea0 + 0x24) = uVar9;
            Ogre::Viewport::setClearEveryFrame(*(Viewport **)(DAT_00920ea0 + 0x24),true,3);
            Ogre::Viewport::setBackgroundColour
                      (*(Viewport **)(DAT_00920ea0 + 0x24),(ColourValue *)White_exref);
            Ogre::Viewport::setOverlaysEnabled(*(Viewport **)(DAT_00920ea0 + 0x24),false);
            Ogre::Viewport::setShadowsEnabled(*(Viewport **)(DAT_00920ea0 + 0x24),false);
            Ogre::Viewport::setVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x24),4);
            basic_string<>("low-noshadow");
            local_8 = 2;
            Ogre::Viewport::setMaterialScheme(*(Viewport **)(DAT_00920ea0 + 0x24),local_60);
            local_8 = 0xffffffff;
            ~basic_string<>();
          }
        }
        uVar9 = 0x40000000;
        puVar8 = local_268;
        Ogre::Math::ATan((float)local_25c);
        uVar9 = FUN_00662dc0(puVar8,uVar9);
        (**(code **)(**(int **)(DAT_00920ea0 + 0x10) + 0x138))(uVar9);
        (**(code **)(**(int **)(DAT_00920ea0 + 0x10) + 0x148))(local_230[4]);
        Ogre::Camera::setPosition
                  (*(Camera **)(DAT_00920ea0 + 0x10),
                   (float)(*(double *)(local_230 + 0x58) - (double)_DAT_025f8e4c),
                   (float)(*(double *)(local_230 + 0x5a) - (double)_DAT_025f8e50),
                   (float)(-*(double *)(local_230 + 0x5c) - (double)_DAT_025f8e54));
        cVar1 = FUN_005cd290();
        if (((cVar1 != '\0') &&
            (*(double *)(local_230 + 0x58) <= 10.0 && *(double *)(local_230 + 0x58) != 10.0)) &&
           (DAT_00920ce0 != 0)) {
          puVar3 = &DAT_00920ca8;
          puVar7 = local_230;
          for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar7 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar7 = puVar7 + 1;
          }
        }
        puVar3 = local_230;
        puVar7 = &DAT_00920ca8;
        for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar7 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar7 = puVar7 + 1;
        }
        puVar3 = (undefined4 *)FUN_008203f0(local_38c,local_230 + 0x10);
        puVar7 = local_1f8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar7 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar7 = puVar7 + 1;
        }
        puVar3 = local_1f8;
        puVar7 = local_1b8;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar7 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar7 = puVar7 + 1;
        }
        pfVar4 = (float *)FUN_0081f1e0(local_2bc,local_1b8);
        local_228 = *pfVar4;
        local_224 = pfVar4[1];
        local_220 = pfVar4[2];
        local_21c = pfVar4[3];
        local_38 = local_228;
        local_34 = local_224;
        local_30 = local_220;
        local_2c = local_21c;
        pQVar5 = (Quaternion *)
                 Ogre::Quaternion::Quaternion(local_2ac,local_21c,local_228,local_224,-local_220);
        Ogre::Camera::setOrientation(*(Camera **)(DAT_00920ea0 + 0x10),pQVar5);
        if (DAT_008eaad8 == 9) {
          uVar6 = Ogre::Viewport::getVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x1c));
          if (uVar6 != 0x10) {
            Ogre::Viewport::setVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x1c),0x10);
            FUN_0044d2a0();
            FUN_00663aa0();
          }
        }
        else {
          uVar6 = Ogre::Viewport::getVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x1c));
          if (uVar6 != 1) {
            Ogre::Viewport::setVisibilityMask(*(Viewport **)(DAT_00920ea0 + 0x1c),1);
            FUN_0044d2a0();
            FUN_00663aa0();
          }
        }
        if (((DAT_008eaad8 == 3) || (DAT_008eaad8 == 9)) ||
           ((DAT_02cd9980 != 0 || (DAT_009454ac != 0)))) {
          FUN_0077c5f0(6);
          FUN_006864f0(0);
        }
        else {
          FUN_0077c5f0(7);
          FUN_006864f0(1);
        }
        iVar2 = FUN_00685520();
        if (iVar2 == 0) {
          FUN_006854d0();
        }
        FUN_00687ac0();
        iVar2 = FUN_00685520();
        if (iVar2 != 0) {
          FUN_006854f0();
        }
        if (DAT_00920c6e == '\0') {
          local_8 = 3;
          Ogre::Root::renderOneFrame(*(Root **)(DAT_00920ea0 + 4));
          FUN_006832b8();
          return;
        }
        DAT_00920c6e = '\0';
        FUN_006832c8();
        return;
      }
      iVar2 = FUN_00685520();
      if (iVar2 != 0) {
        FUN_006854f0();
      }
      FUN_006854b0();
      iVar2 = FUN_00685520();
      if (iVar2 == 0) {
        FUN_006854d0();
      }
      FUN_00822ed0(0x14);
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

