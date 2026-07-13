
int FUN_00443650(void)

{
  int local_8;
  
  local_8 = 0;
  if (DAT_0260d0ec != (int *)0x0) {
    DAT_0260d0ec = (int *)*DAT_0260d0ec;
    if ((DAT_0260d0ec == (int *)0x0) && (DAT_0260d0f4 == &DAT_0260cac4)) {
      DAT_0260d0f4 = &DAT_0260d0f0;
      DAT_0260d0ec = DAT_0260d0f0;
    }
    if (DAT_0260d0ec != (int *)0x0) {
      local_8 = DAT_0260d0ec[2];
    }
  }
  return local_8;
}

