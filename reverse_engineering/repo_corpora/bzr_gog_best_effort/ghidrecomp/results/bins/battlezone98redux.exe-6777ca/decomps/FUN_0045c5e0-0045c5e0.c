
bool __thiscall FUN_0045c5e0(int param_1,byte *param_2)

{
  byte bVar1;
  bool bVar2;
  uint local_14;
  byte *local_10;
  byte *local_c;
  
  local_10 = *(byte **)(param_1 + 4);
  local_c = param_2;
  do {
    bVar1 = *local_c;
    bVar2 = bVar1 < *local_10;
    if (bVar1 != *local_10) {
LAB_0045c635:
      local_14 = -(uint)bVar2 | 1;
      goto LAB_0045c63d;
    }
    if (bVar1 == 0) break;
    bVar1 = local_c[1];
    bVar2 = bVar1 < local_10[1];
    if (bVar1 != local_10[1]) goto LAB_0045c635;
    local_c = local_c + 2;
    local_10 = local_10 + 2;
  } while (bVar1 != 0);
  local_14 = 0;
LAB_0045c63d:
  return local_14 == 0;
}

