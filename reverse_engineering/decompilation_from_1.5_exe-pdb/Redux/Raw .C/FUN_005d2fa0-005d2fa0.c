
void FUN_005d2fa0(void)

{
  void *pvVar1;
  int iVar2;
  undefined4 local_8;
  
  iVar2 = DAT_009182dc * DAT_009182f4;
  for (local_8 = 0; local_8 < iVar2; local_8 = local_8 + 1) {
    pvVar1 = *(void **)(DAT_009182d8 + local_8 * 4);
    if (pvVar1 != (void *)0x0) {
      operator_delete(pvVar1);
    }
  }
  operator_delete__((void *)DAT_009182d8);
  return;
}

