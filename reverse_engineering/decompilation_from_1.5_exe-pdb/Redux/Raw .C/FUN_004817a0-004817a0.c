
byte * FUN_004817a0(int *param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  bool bVar3;
  uint local_1c;
  int *local_18;
  byte *local_14;
  byte *local_10;
  byte *local_c;
  
  if (param_1 == (int *)0x0) {
    local_18 = &DAT_0091739c;
  }
  else {
    local_18 = param_1;
  }
  if ((param_2 != (byte *)0x0) && (*param_2 != 0)) {
    iVar2 = FUN_00481440(param_2);
    for (local_c = *(byte **)(*local_18 + iVar2 * 4); local_c != (byte *)0x0;
        local_c = *(byte **)(local_c + 0x1c)) {
      local_14 = param_2;
      local_10 = local_c;
      do {
        bVar1 = *local_10;
        bVar3 = bVar1 < *local_14;
        if (bVar1 != *local_14) {
LAB_00481852:
          local_1c = -(uint)bVar3 | 1;
          goto LAB_0048185a;
        }
        if (bVar1 == 0) break;
        bVar1 = local_10[1];
        bVar3 = bVar1 < local_14[1];
        if (bVar1 != local_14[1]) goto LAB_00481852;
        local_10 = local_10 + 2;
        local_14 = local_14 + 2;
      } while (bVar1 != 0);
      local_1c = 0;
LAB_0048185a:
      if (local_1c == 0) {
        return local_c;
      }
    }
  }
  return (byte *)0x0;
}

