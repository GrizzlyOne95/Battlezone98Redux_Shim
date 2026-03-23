
uint FUN_00828180(byte *param_1,byte *param_2)

{
  byte bVar1;
  bool bVar2;
  uint local_1c;
  byte *local_10;
  byte *local_c;
  
  local_10 = param_2;
  local_c = param_1;
  do {
    bVar1 = *local_c;
    bVar2 = bVar1 < *local_10;
    if (bVar1 != *local_10) {
LAB_008281db:
      local_1c = -(uint)bVar2 | 1;
      goto LAB_008281e3;
    }
    if (bVar1 == 0) break;
    bVar1 = local_c[1];
    bVar2 = bVar1 < local_10[1];
    if (bVar1 != local_10[1]) goto LAB_008281db;
    local_c = local_c + 2;
    local_10 = local_10 + 2;
  } while (bVar1 != 0);
  local_1c = 0;
LAB_008281e3:
  if (local_1c == 0) {
    if (*(ushort *)(param_2 + 0x10) < *(ushort *)(param_1 + 0x10)) {
      local_1c = 1;
    }
    else if (*(ushort *)(param_1 + 0x10) < *(ushort *)(param_2 + 0x10)) {
      local_1c = 0xffffffff;
    }
    else {
      local_1c = 0;
    }
  }
  return local_1c;
}

