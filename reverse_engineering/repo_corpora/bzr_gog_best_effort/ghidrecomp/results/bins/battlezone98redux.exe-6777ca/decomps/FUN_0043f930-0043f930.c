
void FUN_0043f930(undefined4 param_1,int param_2)

{
  int *piVar1;
  float10 fVar2;
  
  piVar1 = (int *)FUN_0043f2a0();
  if (piVar1 != (int *)0x0) {
    fVar2 = (float10)log2((double)param_2 / 10.0);
    (**(code **)(*piVar1 + 0x3c))(piVar1,(int)((double)fVar2 * 800.0));
  }
  return;
}

