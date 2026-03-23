
undefined4 * FUN_0082c4a6(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (param_2 < 1) {
    if (param_2 < -9999) {
      if (param_2 == -0x2712) {
        puVar2 = (undefined4 *)(param_1 + 0x48);
      }
      else if (param_2 == -0x2711) {
        *(undefined4 *)(param_1 + 0x58) =
             *(undefined4 *)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0xc);
        *(undefined4 *)(param_1 + 0x60) = 5;
        puVar2 = (undefined4 *)(param_1 + 0x58);
      }
      else if (param_2 == -10000) {
        puVar2 = (undefined4 *)(*(int *)(param_1 + 0x10) + 0x60);
      }
      else {
        iVar1 = **(int **)(*(int *)(param_1 + 0x14) + 4);
        puVar2 = (undefined4 *)&DAT_0086ed18;
        if (-0x2712 - param_2 <= (int)(uint)*(byte *)(iVar1 + 7)) {
          puVar2 = (undefined4 *)(iVar1 + (-0x2712 - param_2) * 0x10 + 8);
        }
      }
    }
    else {
      puVar2 = (undefined4 *)(param_2 * 0x10 + *(int *)(param_1 + 8));
    }
  }
  else {
    puVar3 = (undefined4 *)(*(int *)(param_1 + 0xc) + -0x10 + param_2 * 0x10);
    puVar2 = (undefined4 *)&DAT_0086ed18;
    if (puVar3 < *(undefined4 **)(param_1 + 8)) {
      puVar2 = puVar3;
    }
  }
  return puVar2;
}

