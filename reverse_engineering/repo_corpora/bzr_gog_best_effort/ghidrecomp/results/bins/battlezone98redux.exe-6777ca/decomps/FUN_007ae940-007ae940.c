
void FUN_007ae940(void)

{
  undefined1 uVar1;
  MaterialManager *pMVar2;
  uint uVar3;
  
  uVar1 = FUN_007c3cc0();
  *(undefined1 *)(DAT_0094672c + 0x24) = uVar1;
  pMVar2 = Ogre::MaterialManager::getSingleton();
  (**(code **)(*(int *)pMVar2 + 0x8c))(3);
  if (*(char *)(DAT_0094672c + 0x24) == '\0') {
    uVar3 = 1;
    pMVar2 = Ogre::MaterialManager::getSingleton();
    Ogre::MaterialManager::setDefaultAnisotropy(pMVar2,uVar3);
  }
  else {
    uVar3 = 1 << (*(char *)(DAT_0094672c + 0x24) - 1U & 0x1f);
    pMVar2 = Ogre::MaterialManager::getSingleton();
    Ogre::MaterialManager::setDefaultAnisotropy(pMVar2,uVar3);
  }
  return;
}

