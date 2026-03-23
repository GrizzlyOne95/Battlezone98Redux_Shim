
void FUN_0067e430(int param_1,int *param_2,char param_3)

{
  char cVar1;
  uint uVar2;
  Bone *this;
  int local_34;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  basic_string<>(param_1 + 8,8);
  local_8 = 0;
  cVar1 = (**(code **)(*param_2 + 0xdc))(local_2c,uVar2);
  if (cVar1 != '\0') {
    this = (Bone *)(**(code **)(*param_2 + 0xd4))(local_2c);
    Ogre::Bone::setManuallyControlled(this,true);
    (**(code **)(*(int *)this + 0x44))(1);
    *(Bone **)(param_1 + 0xcc) = this;
    FUN_00681cc0(param_1,param_1 + 0x20);
    if (param_3 != '\0') {
      Ogre::Bone::setBindingPose(this);
    }
  }
  for (local_34 = *(int *)(param_1 + 0x80); local_34 != 0; local_34 = *(int *)(local_34 + 0x7c)) {
    FUN_0067e430(local_34,param_2,param_3);
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

