
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0049b2d0(void)

{
  void *pvVar1;
  undefined4 local_c;
  
  pvVar1 = operator_new(0x40);
  if (pvVar1 == (void *)0x0) {
    local_c = 0;
  }
  else {
    local_c = FUN_005b2740((double)_DAT_008e7970,(double)_DAT_008e7960,(double)DAT_02ce99b4,
                           (double)DAT_02ce99bc,(double)DAT_02ce99b0,(double)DAT_02ce99b8,0x1000);
  }
  DAT_009173dc = local_c;
  return;
}

