
uint __fastcall FUN_0073a5d0(int *param_1)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = param_1;
  if ((((uint)param_1[1] >> 0x14 & 0xf) == 0) ||
     (piVar1 = (int *)((uint)param_1[1] >> 0x14 & 0xf), (int *)0xa < piVar1)) {
    uVar2 = (uint)piVar1 & 0xffffff00;
  }
  else if ((param_1[1] >> 0x18 < 1) || (piVar1 = param_1, 4 < param_1[1] >> 0x18)) {
    uVar2 = (uint)piVar1 & 0xffffff00;
  }
  else if ((((uint)param_1[1] >> 0x14 & 0xf) == 1) &&
          ((piVar1 = (int *)0x0, *param_1 == 0 || (piVar1 = param_1, 4 < (param_1[1] & 0xfffffU)))))
  {
    uVar2 = (uint)piVar1 & 0xffffff00;
  }
  else if ((((uint)param_1[1] >> 0x14 & 0xf) == 7) &&
          ((piVar1 = (int *)0x0, *param_1 == 0 || (piVar1 = param_1, (param_1[1] & 0xfffffU) != 0)))
          ) {
    uVar2 = (uint)piVar1 & 0xffffff00;
  }
  else if ((((uint)param_1[1] >> 0x14 & 0xf) == 3) && (*param_1 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

