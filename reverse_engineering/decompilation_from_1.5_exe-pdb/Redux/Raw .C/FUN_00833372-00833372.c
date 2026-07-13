
void FUN_00833372(undefined4 param_1,undefined8 *param_2)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(int *)(param_2 + 1) == 3) {
    sprintf(local_28,"%.14g",*param_2);
    pcVar3 = local_28;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    uVar2 = FUN_008309f4(param_1,local_28,(int)pcVar3 - (int)(local_28 + 1));
    *(undefined4 *)param_2 = uVar2;
    *(undefined4 *)(param_2 + 1) = 4;
  }
  FUN_0083e885();
  return;
}

