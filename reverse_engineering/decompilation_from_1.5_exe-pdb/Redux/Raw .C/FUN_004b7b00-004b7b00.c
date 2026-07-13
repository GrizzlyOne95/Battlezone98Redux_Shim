
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004b7b00(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((*(char *)(param_1 + 0x68) == '\x02') && (*(short *)(param_1 + 0x62) != 0)) {
    DAT_009175c0 = 0x4f43;
    DAT_009175c2 = *(undefined4 *)(param_1 + 100);
    _DAT_009175c6 = param_2;
    unique0x00017200 = *param_3;
    DAT_009175ce = param_3[1];
    DAT_009175d2 = param_3[2];
    uVar2 = 0x16;
    iVar1 = FUN_007659f0(0x16);
    if (iVar1 != 0) {
      FUN_007596b0(*(undefined2 *)(param_1 + 0x62),&DAT_009175c0,uVar2,1);
    }
  }
  return;
}

