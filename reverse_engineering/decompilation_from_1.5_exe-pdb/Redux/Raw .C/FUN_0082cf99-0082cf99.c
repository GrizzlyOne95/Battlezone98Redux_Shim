
void FUN_0082cf99(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)FUN_0082c4a6(param_1,param_2);
  puVar3 = puVar2 + 4;
  if (puVar3 < *(undefined4 **)(param_1 + 8)) {
    do {
      *puVar2 = *puVar3;
      puVar1 = puVar3 + 1;
      puVar3 = puVar3 + 4;
      puVar2[1] = *puVar1;
      puVar2[2] = puVar2[6];
      puVar2 = puVar2 + 4;
    } while (puVar3 < *(undefined4 **)(param_1 + 8));
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -0x10;
  return;
}

