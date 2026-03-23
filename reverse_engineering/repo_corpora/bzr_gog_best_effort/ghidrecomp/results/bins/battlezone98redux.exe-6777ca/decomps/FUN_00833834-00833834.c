
undefined4 FUN_00833834(undefined4 param_1)

{
  int iVar1;
  float10 fVar2;
  
  FUN_0082bbb2(param_1,2,5);
  FUN_0083426a(param_1,0);
  FUN_0082cdd2(param_1,2);
  iVar1 = FUN_0082c9c5(param_1,1);
  if ((iVar1 != 0) && (fVar2 = (float10)FUN_0082d3e1(param_1,1), (double)fVar2 == 0.0)) {
    FUN_0082cdaf(param_1);
    FUN_0082c953(param_1,0xfffffffe);
    FUN_0082d08e(param_1,0xfffffffe);
    return 0;
  }
  iVar1 = FUN_0082c99e(param_1,0xfffffffe);
  if ((iVar1 != 0) || (iVar1 = FUN_0082d08e(param_1,0xfffffffe), iVar1 == 0)) {
    FUN_0082bc39(param_1,"\'setfenv\' cannot change environment of given object");
  }
  return 1;
}

