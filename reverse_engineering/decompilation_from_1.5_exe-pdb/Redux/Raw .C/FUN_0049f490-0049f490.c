
uint FUN_0049f490(void)

{
  uint in_EAX;
  uint uVar1;
  
  if (DAT_00915694 == (int *)0x0) {
    uVar1 = in_EAX & 0xffffff00;
  }
  else {
    uVar1 = (**(code **)(*DAT_00915694 + 0x18))();
  }
  return uVar1;
}

