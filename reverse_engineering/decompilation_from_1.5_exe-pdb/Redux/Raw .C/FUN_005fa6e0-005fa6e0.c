
void __fastcall FUN_005fa6e0(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (param_1[8] != 0) {
    FUN_005fa940();
    param_1[7] = param_1[8];
    param_1[8] = 0;
    FUN_005fa7c0();
  }
  uVar2 = FUN_00473890();
  cVar1 = (**(code **)(*param_1 + 0x24))(uVar2);
  if (cVar1 != '\0') {
    FUN_005fa940();
    uVar3 = FUN_004dbb40();
    (**(code **)(*param_1 + 0x28))(uVar2,uVar3);
    param_1[7] = param_1[8];
    param_1[8] = 0;
    *(undefined1 *)((int)param_1 + 0x4a) = 0;
    FUN_005fa7c0();
    if (param_1[8] != 0) {
      return;
    }
  }
  cVar1 = (**(code **)(*param_1 + 0x2c))();
  if (cVar1 == '\0') {
    FUN_005faac0();
  }
  return;
}

