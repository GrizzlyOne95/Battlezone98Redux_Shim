
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00679f10(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x1c8) != 0) {
    iVar1 = *(int *)(param_1 + 0x1c8);
    iVar2 = *(int *)(param_1 + 0x1d8) - *(int *)(iVar1 + 0x84);
    DAT_02ceb848 = DAT_02ceb848 + 1;
    if (*(int *)(iVar1 + 0x94) == 2) {
      _DAT_02ceb840 = ((uint)(iVar2 - *(int *)(iVar1 + 0x88)) >> 1) + _DAT_02ceb840;
    }
    else if (*(int *)(iVar1 + 0x94) == 4) {
      _DAT_02ceb840 = (uint)(iVar2 - *(int *)(iVar1 + 0x88)) / 3 + _DAT_02ceb840;
    }
    *(int *)(iVar1 + 0x58) = *(int *)(param_1 + 0x1d4) - *(int *)(iVar1 + 0x54);
    *(int *)(iVar1 + 0x88) = iVar2;
  }
  return;
}

