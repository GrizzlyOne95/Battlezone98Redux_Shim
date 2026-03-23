
char * __thiscall FUN_005940e0(char *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_14;
  char *local_10;
  
  DAT_02a13cc4 = param_2;
  DAT_009181a4 = param_1;
  iVar2 = FUN_004623e0();
  if (iVar2 == 0) {
    *param_1 = '\0';
  }
  else {
    local_14 = (char *)FUN_004623e0();
    local_10 = param_1;
    do {
      cVar1 = *local_14;
      *local_10 = cVar1;
      local_14 = local_14 + 1;
      local_10 = local_10 + 1;
    } while (cVar1 != '\0');
  }
  iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
  if (*(int *)(iVar2 + 0x14) == 0x57494e47) {
    DAT_02a13cc0 = FUN_0045bdf0();
  }
  else {
    DAT_02a13cc0 = 0;
  }
  if (DAT_02a13cc0 == 0) {
    param_1[0x30] = '\0';
    param_1[0x31] = '\0';
    param_1[0x32] = '\0';
    param_1[0x33] = '\0';
  }
  else {
    *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(DAT_02a13cc0 + 0x18);
  }
  uVar3 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
  *(undefined4 *)(param_1 + 0x34) = uVar3;
  param_1[0x38] = '\x01';
  return param_1;
}

