
void FUN_005037f0(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar3 = (float10)FUN_0082ba89(param_1,1);
  uVar1 = FUN_0082c225(param_1,2,0,0);
  iVar2 = FUN_0082c9c5(param_1,3,uVar1);
  if (iVar2 == 0) {
    FUN_0045c110((float)fVar3,uVar1);
  }
  else {
    local_20 = FUN_0082d338(param_1,3);
    uStack_1c = FUN_0082d338(param_1,4);
    uStack_18 = FUN_0082d338(param_1,5);
    uStack_14 = FUN_0082d338(param_1,6);
    uStack_10 = FUN_0082d338(param_1,7);
    uStack_c = FUN_0082d338(param_1,8);
    FUN_0045c130((float)fVar3,uVar1,&local_20);
  }
  FUN_0083e885();
  return;
}

