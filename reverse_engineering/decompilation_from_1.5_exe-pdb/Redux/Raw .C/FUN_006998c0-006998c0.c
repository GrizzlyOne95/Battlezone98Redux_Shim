
int FUN_006998c0(int param_1,byte *param_2)

{
  byte bVar1;
  bool bVar2;
  uint local_1c;
  byte *local_14;
  byte *local_10;
  int local_c;
  
  bVar2 = false;
  local_c = *(int *)(param_1 + 4);
  do {
    if ((bVar2) || (local_c == 0)) {
      return local_c;
    }
    local_14 = *(byte **)(local_c + 4);
    local_10 = param_2;
    do {
      bVar1 = *local_10;
      bVar2 = bVar1 < *local_14;
      if (bVar1 != *local_14) {
LAB_00699936:
        local_1c = -(uint)bVar2 | 1;
        goto LAB_0069993e;
      }
      if (bVar1 == 0) break;
      bVar1 = local_10[1];
      bVar2 = bVar1 < local_14[1];
      if (bVar1 != local_14[1]) goto LAB_00699936;
      local_10 = local_10 + 2;
      local_14 = local_14 + 2;
    } while (bVar1 != 0);
    local_1c = 0;
LAB_0069993e:
    bVar2 = local_1c == 0;
    if (!bVar2) {
      local_c = *(int *)(local_c + 0x24);
    }
  } while( true );
}

