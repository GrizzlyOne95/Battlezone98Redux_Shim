
void FUN_0082b87b(int *param_1)

{
  int iVar1;
  int *piVar2;
  void *_Src;
  int iVar3;
  
  piVar2 = param_1;
  iVar1 = param_1[2];
  _Src = (void *)FUN_0082d377(iVar1,0xffffffff,&param_1);
  if ((int *)((int)piVar2 + (0x20c - *piVar2)) < param_1) {
    iVar3 = FUN_0082b708(piVar2);
    if (iVar3 != 0) {
      FUN_0082c953(iVar1,0xfffffffe);
    }
    piVar2[1] = piVar2[1] + 1;
    FUN_0082b690(piVar2);
  }
  else {
    memcpy((void *)*piVar2,_Src,(size_t)param_1);
    *piVar2 = *piVar2 + (int)param_1;
    FUN_0082d226(iVar1,0xfffffffe);
  }
  return;
}

