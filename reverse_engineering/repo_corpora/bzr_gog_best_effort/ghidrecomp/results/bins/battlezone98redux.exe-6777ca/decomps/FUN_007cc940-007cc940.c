
uint __thiscall FUN_007cc940(uint param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  
  uVar1 = param_1;
  if ((((*(char *)(param_1 + 0x92c) != '\0') &&
       (uVar1 = 0, (*(uint *)(param_1 + 0x14) & 0x400) != 0)) &&
      (uVar1 = FUN_007d2810((float)param_2,(float)param_3), (uVar1 & 0xff) != 0)) &&
     ((uVar1 = (uint)*(byte *)(param_1 + 0x92d), uVar1 != 0 && (param_4 == 0)))) {
    *(undefined1 *)(param_1 + 0x92d) = 0;
    return 1;
  }
  return uVar1 & 0xffffff00;
}

