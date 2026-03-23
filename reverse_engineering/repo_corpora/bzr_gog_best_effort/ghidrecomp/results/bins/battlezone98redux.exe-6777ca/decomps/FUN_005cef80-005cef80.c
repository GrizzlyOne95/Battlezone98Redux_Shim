
undefined4 * __thiscall FUN_005cef80(undefined4 *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  double dVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c988;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00584eb0(param_2,param_3);
  local_8 = 0;
  *param_1 = SeismicWave::vftable;
  dVar2 = floor((double)(*(float *)(param_3 + 0x78) * 2.0) * 0.2);
  uVar1 = FUN_0083d92c();
  param_1[0x3d] = uVar1;
  memset((void *)param_1[0x3d],0,((int)dVar2 + 2) * ((int)dVar2 + 2) * 2);
  *(undefined4 *)(param_2 + 0xac) = *(undefined4 *)(param_3 + 0x78);
  ExceptionList = local_10;
  return param_1;
}

