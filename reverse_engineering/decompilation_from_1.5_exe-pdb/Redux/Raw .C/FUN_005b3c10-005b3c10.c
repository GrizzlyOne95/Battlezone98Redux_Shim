
void __fastcall FUN_005b3c10(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x1c) != *(int *)(param_1 + 0x18)) {
    FUN_005b4090();
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x1c);
    FUN_005b3cb0();
  }
  uVar2 = FUN_00473890();
  cVar1 = FUN_005b4530(uVar2);
  if (cVar1 != '\0') {
    FUN_005b4090();
    uVar2 = FUN_004dbb40();
    FUN_005b4740(uVar2);
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x1c);
    FUN_005b3cb0();
  }
  FUN_005b41d0();
  return;
}

