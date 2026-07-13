
void __fastcall FUN_007055a0(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  param_1[6] = param_1[6] + 1;
  param_1[2] = param_1[2] + 1;
  iVar2 = FUN_006ae390(param_1);
  if (param_1[2] == iVar2) {
    param_1[4] = param_1[4] + 8;
    param_1[2] = 0;
    while (param_1[4] != param_1[5]) {
      uVar1 = ((undefined4 *)param_1[4])[1];
      *param_1 = *(undefined4 *)param_1[4];
      param_1[1] = uVar1;
      iVar2 = FUN_006ae390(param_1);
      if (iVar2 != 0) {
        return;
      }
      param_1[4] = param_1[4] + 8;
    }
  }
  return;
}

