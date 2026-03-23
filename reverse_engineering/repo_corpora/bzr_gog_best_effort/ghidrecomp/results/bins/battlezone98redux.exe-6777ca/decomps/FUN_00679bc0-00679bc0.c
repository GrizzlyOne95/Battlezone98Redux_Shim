
void FUN_00679bc0(undefined4 param_1,int param_2,float param_3)

{
  char cVar1;
  bool bVar2;
  char cVar3;
  float *pfVar4;
  undefined4 uVar5;
  undefined4 local_38;
  int *local_34;
  int *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a048;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_38 = 0;
  pfVar4 = (float *)FUN_0067ba40(&param_3,&local_38,local_14);
  param_3 = *pfVar4;
  if (((local_30[0x72] != 0) && (*(int *)(local_30[0x72] + 0x94) == param_2)) &&
     (*(float *)(local_30[0x72] + 0xb0) == param_3 * param_3)) {
    local_34 = (int *)get();
    uVar5 = (**(code **)(*local_34 + 0x58))(param_1);
    cVar1 = operator!=<>(uVar5);
    if (cVar1 == '\0') {
      bVar2 = Ogre::Renderable::getUseIdentityProjection((Renderable *)local_30[0x72]);
      if (bVar2 == (bool)(char)local_30[0x54]) {
        bVar2 = Ogre::Renderable::getUseIdentityView((Renderable *)local_30[0x72]);
        if (bVar2 == (bool)*(char *)((int)local_30 + 0x151)) {
          cVar1 = *(char *)(local_30[0x72] + 0xac);
          cVar3 = (**(code **)(*local_30 + 0xb0))();
          if (cVar1 == cVar3) goto LAB_00679d4a;
        }
      }
    }
  }
  FUN_00679830(0);
  basic_string<>(param_1);
  local_8 = 0;
  FUN_006799c0(local_2c,param_2,param_3 * param_3);
  local_8 = 0xffffffff;
  ~basic_string<>();
LAB_00679d4a:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

