
int FUN_006b20f0(int *param_1,int param_2,int param_3)

{
  int iVar1;
  
  LOCK();
  iVar1 = *param_1;
  if (param_3 == iVar1) {
    *param_1 = param_2;
    iVar1 = param_3;
  }
  UNLOCK();
  return iVar1;
}

