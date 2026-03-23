
void FUN_004dfa20(void)

{
  void *pvVar1;
  undefined4 local_c;
  
  pvVar1 = operator_new(0x40);
  if (pvVar1 == (void *)0x0) {
    local_c = 0;
  }
  else {
    local_c = FUN_005b2740(0x4064000000000000,0x4064000000000000,(double)DAT_02ce99b4,
                           (double)DAT_02ce99bc,(double)DAT_02ce99b0,(double)DAT_02ce99b8,0x1000);
  }
  DAT_00917a6c = local_c;
  return;
}

