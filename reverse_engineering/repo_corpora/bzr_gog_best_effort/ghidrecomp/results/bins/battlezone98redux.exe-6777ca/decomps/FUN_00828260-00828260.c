
uint FUN_00828260(byte *param_1,byte *param_2)

{
  byte bVar1;
  bool bVar2;
  byte *local_10;
  byte *local_c;
  
  local_10 = param_2;
  local_c = param_1;
  while( true ) {
    bVar1 = *local_c;
    bVar2 = bVar1 < *local_10;
    if (bVar1 != *local_10) break;
    if (bVar1 == 0) {
      return 0;
    }
    bVar1 = local_c[1];
    bVar2 = bVar1 < local_10[1];
    if (bVar1 != local_10[1]) break;
    local_c = local_c + 2;
    local_10 = local_10 + 2;
    if (bVar1 == 0) {
      return 0;
    }
  }
  return -(uint)bVar2 | 1;
}

