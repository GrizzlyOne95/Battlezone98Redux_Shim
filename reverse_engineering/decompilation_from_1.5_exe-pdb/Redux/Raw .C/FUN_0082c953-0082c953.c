
void FUN_0082c953(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined4 *)FUN_0082c4a6(param_1,param_2);
  for (puVar2 = *(undefined4 **)(param_1 + 8); puVar1 < puVar2; puVar2 = puVar2 + -4) {
    *puVar2 = puVar2[-4];
    puVar2[1] = puVar2[-3];
    puVar2[2] = puVar2[-2];
  }
  puVar2 = *(undefined4 **)(param_1 + 8);
  *puVar1 = *puVar2;
  puVar1[1] = puVar2[1];
  puVar1[2] = puVar2[2];
  return;
}

