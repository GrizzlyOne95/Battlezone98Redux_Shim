
int __thiscall FUN_00838733(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  float10 fVar2;
  int iVar3;
  
  fVar2 = (float10)FUN_0082d3e1(param_2,param_3,param_1,param_1);
  iVar3 = SUB84((double)(fVar2 + (float10)6755399441055744.0),0);
  if (iVar3 == 0) {
    iVar1 = FUN_0082c9c5(param_2,param_3);
    if (iVar1 == 0) {
      FUN_0082c308(param_2,param_3,"number");
    }
  }
  return iVar3;
}

