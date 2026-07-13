
void FUN_00685ef0(void)

{
  char cVar1;
  int *piVar2;
  MeshManager *pMVar3;
  undefined8 uVar4;
  
  FUN_00685ea0(&DAT_00920ee8);
  FUN_00685ea0(&DAT_00920ef0);
  FUN_00685ea0(&DAT_00920eec);
  FUN_00685d70(&DAT_00920ee0);
  FUN_00685d70(&DAT_00920ee4);
  FUN_00685d70(&DAT_00920ed8);
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    piVar2 = (int *)get();
    pMVar3 = Ogre::MeshManager::getSingleton();
    uVar4 = (**(code **)(*piVar2 + 0x5c))();
    (**(code **)(*(int *)pMVar3 + 0x34))(uVar4);
    FUN_004c85d0();
  }
  DAT_00945498 = 0;
  return;
}

