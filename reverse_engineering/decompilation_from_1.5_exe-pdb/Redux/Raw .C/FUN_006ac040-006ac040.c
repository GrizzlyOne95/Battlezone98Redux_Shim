
void FUN_006ac040(int *param_1)

{
  int iVar1;
  
  LOCK();
  iVar1 = *param_1;
  *param_1 = *param_1 + -1;
  UNLOCK();
  if (iVar1 == 1) {
    WSACleanup();
  }
  return;
}

