
void __thiscall FUN_00661ac0(int param_1,float param_2)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  Material *pMVar4;
  Technique *pTVar5;
  Pass *pPVar6;
  ColourValue *pCVar7;
  GpuProgramParameters *pGVar8;
  undefined4 uVar9;
  ushort uVar10;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar11;
  ushort uVar12;
  float fVar13;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  undefined1 local_48 [20];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  int local_2c;
  Technique *local_28;
  GpuNamedConstants *local_24;
  Pass *local_20;
  int local_1c;
  ushort local_18;
  ushort local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084da76;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(float *)(param_1 + 0x14) != param_2) {
    *(float *)(param_1 + 0x14) = param_2;
    if (*(float *)(param_1 + 0x14) <= 0.0) {
      *(undefined4 *)(param_1 + 0x14) = 0;
    }
    else {
      local_1c = param_1;
      Ogre::ColourValue::ColourValue((ColourValue *)&local_74,1.0,1.0,1.0,1.0);
      Ogre::ColourValue::ColourValue((ColourValue *)&local_64,1.0,1.0,1.0,1.0);
      if (1.0 < *(float *)(local_1c + 0x14)) {
        *(undefined4 *)(local_1c + 0x14) = 0x3f800000;
      }
      cVar1 = FUN_004c85a0(uVar3);
      if (cVar1 != '\0') {
        FUN_00661f20();
      }
      local_18 = 0;
      pMVar4 = (Material *)get(local_48);
      Ogre::Material::getTechniqueIterator(pMVar4);
      while (cVar1 = FUN_006624a0(), cVar1 != '\0') {
        local_28 = (Technique *)FUN_00662470();
        Ogre::Technique::getPassIterator(local_28);
        local_14 = 0;
        while (cVar1 = FUN_006624a0(), cVar1 != '\0') {
          uVar10 = local_18;
          uVar12 = local_14;
          pMVar4 = (Material *)get();
          pTVar5 = Ogre::Material::getTechnique(pMVar4,uVar10);
          pPVar6 = Ogre::Technique::getPass(pTVar5,uVar12);
          pCVar7 = Ogre::Pass::getDiffuse(pPVar6);
          local_74 = *(float *)pCVar7;
          local_70 = *(float *)(pCVar7 + 4);
          local_6c = *(float *)(pCVar7 + 8);
          local_68 = *(float *)(pCVar7 + 0xc);
          local_20 = (Pass *)FUN_00662470();
          local_2c = *(int *)(local_1c + 0x18);
          if (local_2c == 2) {
            local_58 = local_68;
            local_64 = local_74 - local_74 * *(float *)(local_1c + 0x14);
            local_60 = local_70 - local_70 * *(float *)(local_1c + 0x14);
            local_5c = local_6c - local_6c * *(float *)(local_1c + 0x14);
            Ogre::Pass::setAmbient(local_20,(ColourValue *)Black_exref);
          }
          else {
            uVar10 = local_18;
            uVar12 = local_14;
            pMVar4 = (Material *)get();
            pTVar5 = Ogre::Material::getTechnique(pMVar4,uVar10);
            pPVar6 = Ogre::Technique::getPass(pTVar5,uVar12);
            pCVar7 = Ogre::Pass::getAmbient(pPVar6);
            local_64 = *(float *)pCVar7;
            local_60 = *(float *)(pCVar7 + 4);
            local_5c = *(float *)(pCVar7 + 8);
            local_58 = (1.0 - *(float *)(local_1c + 0x14)) * *(float *)(pCVar7 + 0xc);
            Ogre::Pass::setAmbient(local_20,(ColourValue *)&local_64);
            local_64 = local_74;
            local_60 = local_70;
            local_5c = local_6c;
            local_58 = (1.0 - *(float *)(local_1c + 0x14)) * local_68;
          }
          bVar2 = Ogre::Pass::hasGpuProgram(local_20,1);
          if (bVar2) {
            Ogre::Pass::getFragmentProgramParameters(local_20);
            local_8 = 0;
            cVar1 = FUN_004c85a0();
            if (cVar1 == '\0') {
              pGVar8 = (GpuProgramParameters *)get();
              bVar2 = Ogre::GpuProgramParameters::hasNamedParameters(pGVar8);
              if (bVar2) {
                if ((DAT_02cc32e0 & 1) == 0) {
                  DAT_02cc32e0 = DAT_02cc32e0 | 1;
                  local_8._0_1_ = 1;
                  basic_string<>("transparency");
                  FUN_0083e979(FUN_008677b0);
                  local_8 = (uint)local_8._1_3_ << 8;
                }
                pGVar8 = (GpuProgramParameters *)get();
                local_24 = Ogre::GpuProgramParameters::getConstantDefinitions(pGVar8);
                uVar9 = FID_conflict_begin(local_30);
                FUN_00421e00(local_34,&DAT_02cc3300);
                cVar1 = FUN_00420f10(uVar9);
                if (cVar1 != '\0') {
                  pbVar11 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)&DAT_02cc3300;
                  fVar13 = local_58;
                  pGVar8 = (GpuProgramParameters *)get();
                  Ogre::GpuProgramParameters::setNamedConstant(pGVar8,pbVar11,fVar13);
                }
              }
            }
            local_8 = 0xffffffff;
            FUN_004499a0();
          }
          Ogre::Pass::setDiffuse(local_20,(ColourValue *)&local_64);
          local_14 = local_14 + 1;
        }
        local_18 = local_18 + 1;
      }
    }
  }
  ExceptionList = local_10;
  return;
}

