
uint FUN_0062c850(void)

{
  uint uVar1;
  
  if (DAT_00920c78 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(uint *)(*(int *)(*DAT_00920c78 + 0x88) + 0x114) & 0x20;
  }
  return uVar1;
}

