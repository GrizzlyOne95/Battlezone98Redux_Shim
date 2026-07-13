
int FUN_00687ce0(void)

{
  bool bVar1;
  int local_10;
  int local_c;
  
  local_10 = 0;
  bVar1 = false;
  local_c = 0;
  do {
    if (199 < local_c) {
LAB_00687d2a:
      if (!bVar1) {
        local_10 = -1;
      }
      return local_10;
    }
    if (*(int *)(&DAT_02b7a4ac + local_c * 0x97c) == 0) {
      local_10 = local_c;
      bVar1 = true;
      goto LAB_00687d2a;
    }
    local_c = local_c + 1;
  } while( true );
}

