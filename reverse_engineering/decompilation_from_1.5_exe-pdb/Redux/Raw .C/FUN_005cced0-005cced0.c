
float10 __thiscall FUN_005cced0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = FUN_00462630(param_2,param_1);
  if (iVar1 == 0) {
    fVar2 = (float10)0;
  }
  else {
    fVar2 = (float10)(**(code **)(*(int *)(iVar1 + 0x18) + 0x1c))();
  }
  return fVar2;
}

