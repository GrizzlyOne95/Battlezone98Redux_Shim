
void FUN_00823390(int param_1,int param_2)

{
  int iVar1;
  undefined1 local_2c [24];
  uint local_14;
  int local_10;
  int local_c;
  undefined4 *local_8;
  
  local_c = *(int *)(param_1 + 8);
  if (param_2 != 0) {
    for (local_8 = DAT_02cc1b40; local_8 != (undefined4 *)0x0; local_8 = (undefined4 *)*local_8) {
      local_10 = local_8[2];
      *(uint *)(local_10 + 0x120) = *(uint *)(local_10 + 0x120) & 0xfffffeff;
    }
  }
  *(uint *)(local_c + 0x120) = *(uint *)(local_c + 0x120) & 0xfffffeff;
  if (param_2 == 0) {
    local_14 = 0;
  }
  else {
    local_14 = 0x100;
  }
  *(uint *)(local_c + 0x120) = *(uint *)(local_c + 0x120) | local_14;
  do {
    iVar1 = _Val_type<>(local_2c,0,0x100,0x100,1);
  } while (iVar1 != 0);
  do {
    iVar1 = _Val_type<>(local_2c,0,0x102,0x102,1);
  } while (iVar1 != 0);
  return;
}

