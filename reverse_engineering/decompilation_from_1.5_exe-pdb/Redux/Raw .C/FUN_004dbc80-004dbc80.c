
uint __fastcall FUN_004dbc80(uint param_1)

{
  uint uVar1;
  
  if (param_1 == DAT_00917afc) {
    uVar1 = param_1 & 0xffffff00;
  }
  else {
    uVar1 = *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x200;
    if (uVar1 == 0) {
      if (*(int *)(param_1 + 0xfc) == 0) {
        uVar1 = 0;
      }
      else if (*(int *)(param_1 + 0xa8) == 0) {
        uVar1 = 1;
      }
      else {
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}

