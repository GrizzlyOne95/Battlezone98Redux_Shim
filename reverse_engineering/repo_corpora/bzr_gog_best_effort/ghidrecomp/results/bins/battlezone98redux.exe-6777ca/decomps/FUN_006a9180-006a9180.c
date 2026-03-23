
undefined4 FUN_006a9180(void)

{
  IGalaxy *pIVar1;
  undefined4 uVar2;
  
  pIVar1 = galaxy::api::GalaxyFactory::GetInstance();
  if (pIVar1 == (IGalaxy *)0x0) {
    uVar2 = 0;
  }
  else {
    pIVar1 = galaxy::api::GalaxyFactory::GetInstance();
    uVar2 = (**(code **)(*(int *)pIVar1 + 0x28))();
  }
  return uVar2;
}

