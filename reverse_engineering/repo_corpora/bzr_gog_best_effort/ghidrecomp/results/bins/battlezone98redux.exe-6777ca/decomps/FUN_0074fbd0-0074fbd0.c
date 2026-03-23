
undefined4 * __thiscall FUN_0074fbd0(undefined4 *param_1,undefined4 param_2)

{
  IGalaxy *pIVar1;
  undefined4 uVar2;
  int *local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fda8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00750510(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = galaxy::api::SelfRegisteringListener<class_galaxy::api::ILobbyListListener>::vftable;
  param_1[1] = param_2;
  if (param_1[1] == 0) {
    pIVar1 = galaxy::api::GalaxyFactory::GetInstance();
    local_20 = (int *)(**(code **)(*(int *)pIVar1 + 0x38))();
  }
  else {
    local_20 = (int *)param_1[1];
  }
  if (local_20 != (int *)0x0) {
    uVar2 = _Val_type<>(param_1);
    (**(code **)(*local_20 + 4))(uVar2);
  }
  ExceptionList = local_10;
  return param_1;
}

