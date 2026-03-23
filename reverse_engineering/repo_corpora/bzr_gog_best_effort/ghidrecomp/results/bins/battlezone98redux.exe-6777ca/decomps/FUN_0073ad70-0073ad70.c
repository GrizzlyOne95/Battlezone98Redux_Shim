
void FUN_0073ad70(void)

{
  IGalaxy *pIVar1;
  
  pIVar1 = galaxy::api::GalaxyFactory::GetInstance();
  if (pIVar1 != (IGalaxy *)0x0) {
    pIVar1 = galaxy::api::GalaxyFactory::GetInstance();
    (**(code **)(*(int *)pIVar1 + 0x10))();
    galaxy::api::GalaxyFactory::ResetInstance();
  }
  return;
}

