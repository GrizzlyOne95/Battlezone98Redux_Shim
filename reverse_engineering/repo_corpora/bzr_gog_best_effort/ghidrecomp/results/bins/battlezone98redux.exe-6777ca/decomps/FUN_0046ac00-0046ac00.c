
void FUN_0046ac00(void)

{
  int local_8;
  
  operator_delete__(DAT_0260d178);
  DAT_0260d178 = (void *)0x0;
  operator_delete__(DAT_0260d17c);
  DAT_0260d17c = (void *)0x0;
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    operator_delete__(*(void **)(&DAT_0260d118 + local_8 * 4));
    *(undefined4 *)(&DAT_0260d118 + local_8 * 4) = 0;
  }
  operator_delete__(DAT_0260d180);
  DAT_0260d180 = (void *)0x0;
  FUN_00429ce0();
  FUN_00429ce0();
  return;
}

