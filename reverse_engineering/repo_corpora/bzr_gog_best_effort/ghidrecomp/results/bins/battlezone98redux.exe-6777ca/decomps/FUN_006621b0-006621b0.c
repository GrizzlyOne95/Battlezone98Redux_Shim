
void FUN_006621b0(void)

{
  char cVar1;
  int *piVar2;
  MaterialManager *pMVar3;
  undefined4 uVar4;
  undefined4 extraout_var;
  
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    uVar4 = extraout_var;
    piVar2 = (int *)get();
    pMVar3 = Ogre::MaterialManager::getSingleton();
    uVar4 = (**(code **)(*piVar2 + 0x58))(pMVar3,piVar2,uVar4);
    (**(code **)(*(int *)pMVar3 + 0x38))(uVar4);
  }
  FUN_004c85d0();
  return;
}

