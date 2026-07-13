
void FUN_005c5870(void)

{
  void *pvVar1;
  undefined4 local_c;
  
  pvVar1 = operator_new(0x40);
  if (pvVar1 == (void *)0x0) {
    local_c = 0;
  }
  else {
    local_c = FUN_005b2740(0x4054000000000000,0x4054000000000000,(double)DAT_02ce99b4,
                           (double)DAT_02ce99bc,(double)DAT_02ce99b0,(double)DAT_02ce99b8,0x1000);
  }
  DAT_009181bc = local_c;
  DAT_009180d6 = 1;
  return;
}

