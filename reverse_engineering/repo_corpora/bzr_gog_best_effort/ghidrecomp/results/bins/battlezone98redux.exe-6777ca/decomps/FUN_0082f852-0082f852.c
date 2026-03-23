
undefined4 FUN_0082f852(int param_1,char *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  char *pcVar4;
  
  puVar2 = (undefined4 *)**(int **)(param_1 + 0x14);
  *(undefined4 **)(param_1 + 8) = puVar2;
  pcVar4 = param_2;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  uVar3 = FUN_008309f4(param_1,param_2,(int)pcVar4 - (int)(param_2 + 1));
  *puVar2 = uVar3;
  puVar2[2] = 4;
  if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x11) {
    FUN_0082f194(param_1,1);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return 2;
}

