
undefined4 FUN_00763430(void)

{
  IGalaxy *pIVar1;
  undefined4 uVar2;
  
  pIVar1 = galaxy::api::GalaxyFactory::GetInstance();
  if (pIVar1 == (IGalaxy *)0x0) {
    uVar2 = 0;
  }
  else {
    pIVar1 = galaxy::api::GalaxyFactory::GetInstance();
    uVar2 = (**(code **)(*(int *)pIVar1 + 0x20))();
  }
  return uVar2;
}

