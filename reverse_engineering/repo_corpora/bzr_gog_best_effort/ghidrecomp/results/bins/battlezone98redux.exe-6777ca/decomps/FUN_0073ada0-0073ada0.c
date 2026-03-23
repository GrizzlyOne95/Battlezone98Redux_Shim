
void FUN_0073ada0(void)

{
  IGalaxy *pIVar1;
  
  pIVar1 = galaxy::api::GalaxyFactory::GetInstance();
  if (pIVar1 != (IGalaxy *)0x0) {
    pIVar1 = galaxy::api::GalaxyFactory::GetInstance();
    (**(code **)(*(int *)pIVar1 + 0x40))();
  }
  return;
}

