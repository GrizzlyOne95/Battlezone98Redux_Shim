
void __thiscall FUN_004df370(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  float10 fVar2;
  
  piVar1 = (int *)FUN_00479f30(param_2,param_1);
  if (piVar1 != (int *)0x0) {
    fVar2 = (float10)FUN_00822d60();
    (**(code **)(*piVar1 + 0x40))((float)fVar2);
  }
  return;
}

