
void FUN_0043c790(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_009155bc != (int *)0x0) {
    (**(code **)(*DAT_009155bc + 0x48))(DAT_009155bc);
    iVar1 = ___scrt_is_ucrt_dll_in_use(param_1);
    if (iVar1 != 0) {
      (**(code **)(*DAT_009155b8 + 8))(DAT_009155b8);
    }
    (**(code **)(*DAT_009155bc + 8))(DAT_009155bc);
    DAT_009155bc = (int *)0x0;
    DAT_009155b8 = (int *)0x0;
  }
  return;
}

