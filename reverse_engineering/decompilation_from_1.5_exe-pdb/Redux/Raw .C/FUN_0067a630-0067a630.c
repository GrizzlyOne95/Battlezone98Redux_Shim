
undefined1 FUN_0067a630(void)

{
  ushort uVar1;
  char cVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 local_30 [4];
  SceneBlendOperation local_2c;
  SceneBlendFactor local_28;
  Technique *local_24;
  undefined1 local_20 [4];
  Pass *local_1c;
  Technique *local_18;
  Material *local_14;
  SceneBlendFactor local_10;
  ushort local_c;
  undefined1 local_5;
  
  local_14 = (Material *)get();
  FUN_0044eb20(local_20,&local_14);
  uVar4 = FUN_0044eaa0(local_30);
  cVar2 = FUN_00420f10(uVar4);
  if (cVar2 == '\0') {
    if (local_14 == (Material *)0x0) {
      local_24 = (Technique *)0x0;
    }
    else {
      local_24 = Ogre::Material::getBestTechnique(local_14,0,(Renderable *)0x0);
    }
    local_18 = local_24;
    if (local_24 == (Technique *)0x0) {
      local_5 = 1;
    }
    else {
      local_5 = 0;
      local_c = 0;
      while( true ) {
        uVar1 = local_c;
        uVar3 = Ogre::Technique::getNumPasses(local_18);
        if (uVar3 <= uVar1) break;
        local_1c = Ogre::Technique::getPass(local_18,local_c);
        local_28 = Ogre::Pass::getDestBlendFactor(local_1c);
        local_10 = Ogre::Pass::getSourceBlendFactor(local_1c);
        local_2c = Ogre::Pass::getSceneBlendingOperation(local_1c);
        if ((((local_28 != 0) || (local_10 == 6)) || (local_10 == 2)) ||
           (((local_10 == 8 || (local_10 == 4)) || (local_2c == 1)))) {
          local_5 = 1;
          break;
        }
        local_c = local_c + 1;
      }
      puVar6 = (undefined1 *)FUN_0067ae70(&local_14);
      *puVar6 = local_5;
    }
  }
  else {
    iVar5 = FUN_0042da60();
    local_5 = *(undefined1 *)(iVar5 + 4);
  }
  return local_5;
}

