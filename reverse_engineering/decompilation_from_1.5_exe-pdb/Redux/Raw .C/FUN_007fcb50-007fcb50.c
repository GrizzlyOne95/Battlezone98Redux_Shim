
void __thiscall FUN_007fcb50(undefined4 *param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    *param_1 = *param_2;
    cVar1 = FUN_007d7500();
    if (cVar1 == '\0') {
      puVar2 = (undefined4 *)FUN_007d9580(param_2 + 2,param_1 + 2,0);
      (*(code *)*puVar2)();
    }
    else {
      param_1[2] = param_2[2];
      param_1[3] = param_2[3];
      param_1[4] = param_2[4];
      param_1[5] = param_2[5];
      param_1[6] = param_2[6];
      param_1[7] = param_2[7];
    }
  }
  return;
}

