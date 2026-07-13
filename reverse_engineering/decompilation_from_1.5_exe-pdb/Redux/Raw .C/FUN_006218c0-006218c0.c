
undefined4 __thiscall
FUN_006218c0(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,
            undefined4 *param_5,undefined4 *param_6,undefined4 *param_7)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0061e420(param_2,param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else if (*(int *)(iVar1 + 8) == 0) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *(undefined4 *)(iVar1 + 0xc);
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = *(undefined4 *)(iVar1 + 0x10);
    }
    if (param_5 != (undefined4 *)0x0) {
      *param_5 = *(undefined4 *)(iVar1 + 0x14);
    }
    if (param_6 != (undefined4 *)0x0) {
      *param_6 = *(undefined4 *)(iVar1 + 0x18);
    }
    if (param_7 != (undefined4 *)0x0) {
      *param_7 = *(undefined4 *)(iVar1 + 0x1c);
    }
    uVar2 = *(undefined4 *)(iVar1 + 4);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

