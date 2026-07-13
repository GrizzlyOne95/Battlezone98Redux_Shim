
int __thiscall FUN_0081c380(int *param_1,byte *param_2)

{
  byte bVar1;
  bool bVar2;
  uint local_1c;
  byte *local_14;
  byte *local_10;
  int local_c;
  
  local_c = 0;
  do {
    if (*param_1 <= local_c) {
      return 0;
    }
    local_14 = (byte *)(param_1 + local_c * 0x81 + 1);
    local_10 = param_2;
    do {
      bVar1 = *local_10;
      bVar2 = bVar1 < *local_14;
      if (bVar1 != *local_14) {
LAB_0081c3fd:
        local_1c = -(uint)bVar2 | 1;
        goto LAB_0081c405;
      }
      if (bVar1 == 0) break;
      bVar1 = local_10[1];
      bVar2 = bVar1 < local_14[1];
      if (bVar1 != local_14[1]) goto LAB_0081c3fd;
      local_10 = local_10 + 2;
      local_14 = local_14 + 2;
    } while (bVar1 != 0);
    local_1c = 0;
LAB_0081c405:
    if (local_1c == 0) {
      return param_1[local_c * 0x81 + 0x81];
    }
    local_c = local_c + 1;
  } while( true );
}

