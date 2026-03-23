
void __fastcall FUN_004b9940(int *param_1)

{
  int iVar1;
  float10 fVar2;
  int *local_20;
  
  if ((char)param_1[0x1a] != '\x01') {
    iVar1 = (**(code **)(*param_1 + 0x30))();
    if (iVar1 != 0) {
      FUN_0062de40(iVar1,0x280);
    }
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined2 *)((int)param_1 + 0x62) = 0;
    FUN_004badc0(param_1 + 0x19);
    DAT_009175c0 = 0x4f50;
    fVar2 = (float10)FUN_00822d80();
    DAT_009175c2 = (float)fVar2;
    DAT_009175c6 = 6;
    iVar1 = FUN_00417c70();
    if (iVar1 == 0) {
      local_20 = (int *)0x0;
    }
    else {
      local_20 = (int *)(iVar1 + 0x18);
    }
    DAT_009175c7 = (param_1 == local_20) << 7 | 3;
    DAT_009175c8 = param_1[0x19];
    FUN_00575890(&DAT_009175c0,0xc,1,0);
    FUN_004b7bd0();
    iVar1 = (**(code **)*param_1)();
    if ((iVar1 != 0) && (*(int *)(iVar1 + 0x14) == 0x53435250)) {
      (**(code **)(*param_1 + 0x10))();
    }
  }
  return;
}

