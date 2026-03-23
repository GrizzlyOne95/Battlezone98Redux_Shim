
undefined4 FUN_004435f0(void)

{
  undefined4 local_8;
  
  if (DAT_0260cac4 == 0) {
    DAT_0260d0f4 = &DAT_0260d0f0;
    DAT_0260d0ec = DAT_0260d0f0;
  }
  else {
    DAT_0260d0f4 = &DAT_0260cac4;
    DAT_0260d0ec = DAT_0260cac4;
  }
  if (DAT_0260d0ec == 0) {
    local_8 = 0;
  }
  else {
    local_8 = *(undefined4 *)(DAT_0260d0ec + 8);
  }
  return local_8;
}

