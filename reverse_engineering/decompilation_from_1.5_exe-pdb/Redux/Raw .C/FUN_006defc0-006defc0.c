
/* WARNING: Removing unreachable block (ram,0x006defdf) */

uint FUN_006defc0(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  longlong lVar3;
  
  lVar3 = FUN_006e2a00();
  if (lVar3 < 1) {
    uVar1 = 0;
  }
  else {
    lVar3 = FUN_006e2a20();
    iVar2 = (int)((ulonglong)lVar3 >> 0x20);
    uVar1 = (uint)lVar3;
    if (lVar3 == 0) {
      uVar1 = 1;
    }
    else if (((int)param_2 >> 0x1f <= iVar2) &&
            (((int)param_2 >> 0x1f < iVar2 || (param_2 < uVar1)))) {
      uVar1 = param_2;
    }
  }
  return uVar1;
}

