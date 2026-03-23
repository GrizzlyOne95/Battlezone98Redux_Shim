
void __fastcall FUN_0074f6d0(undefined4 *param_1)

{
  uint uVar1;
  IGalaxy *pIVar2;
  undefined4 uVar3;
  int *local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fda8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = galaxy::api::SelfRegisteringListener<class_galaxy::api::ILobbyDataListener>::vftable;
  local_8 = 0;
  if (param_1[1] == 0) {
    pIVar2 = galaxy::api::GalaxyFactory::GetInstance();
    local_20 = (int *)(**(code **)(*(int *)pIVar2 + 0x38))();
  }
  else {
    local_20 = (int *)param_1[1];
  }
  if (local_20 != (int *)0x0) {
    uVar3 = FUN_00750800(param_1,uVar1);
    (**(code **)(*local_20 + 8))(uVar3);
  }
  local_8 = 0xffffffff;
  FUN_006a9f30();
  ExceptionList = local_10;
  return;
}

