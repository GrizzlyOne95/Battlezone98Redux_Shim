
void __fastcall FUN_00449a30(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  *param_1 = iVar1 + -1;
  if (iVar1 + -1 == 0) {
    LOCK();
    param_1[1] = 0;
    UNLOCK();
    FUN_00448d90();
  }
  return;
}

