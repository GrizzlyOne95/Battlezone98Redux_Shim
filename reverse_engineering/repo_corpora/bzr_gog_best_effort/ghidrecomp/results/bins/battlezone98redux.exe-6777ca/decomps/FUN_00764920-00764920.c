
void FUN_00764920(void)

{
  void *pvVar1;
  undefined4 local_c;
  
  if (DAT_00945463 != '\0') {
    if (DAT_00945480 == 0) {
      pvVar1 = operator_new(0x50);
      if (pvVar1 == (void *)0x0) {
        local_c = 0;
      }
      else {
        local_c = FUN_00765cd0();
      }
      DAT_00945480 = local_c;
    }
    FUN_00765d80();
  }
  return;
}

