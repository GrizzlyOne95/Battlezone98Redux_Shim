
void __thiscall FUN_00679ac0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  Renderable *this;
  Renderable RVar1;
  undefined4 uVar2;
  
  this = (Renderable *)param_1[0x72];
  RVar1 = (Renderable)(**(code **)(*param_1 + 0xb0))();
  this[0xac] = RVar1;
  FUN_0067a4a0(param_2);
  FUN_0067a760(param_3);
  FUN_0067a780(param_4);
  Ogre::Renderable::setUseIdentityProjection(this,SUB41(param_1[0x54],0));
  Ogre::Renderable::setUseIdentityView(this,*(bool *)((int)param_1 + 0x151));
  *(int *)(this + 0x78) = param_1[100];
  *(int *)(this + 0x54) = param_1[0x75];
  *(undefined4 *)(this + 0x58) = 0;
  *(int *)(this + 0x8c) = param_1[0x65];
  *(int *)(this + 0x84) = param_1[0x76];
  *(undefined4 *)(this + 0x88) = 0;
  uVar2 = size();
  *(undefined4 *)(this + 0x2c) = uVar2;
  return;
}

