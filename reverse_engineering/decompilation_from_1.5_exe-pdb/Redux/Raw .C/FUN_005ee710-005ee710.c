
void __fastcall FUN_005ee710(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x1c) != *(int *)(param_1 + 0x18)) {
    FUN_005eec50();
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x1c);
    FUN_005ee7b0();
  }
  uVar2 = FUN_00473890();
  cVar1 = FUN_005ef8b0(uVar2);
  if (cVar1 != '\0') {
    FUN_005eec50();
    uVar2 = FUN_004dbb40();
    FUN_005efac0(uVar2);
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x1c);
    FUN_005ee7b0();
  }
  FUN_005eecd0();
  return;
}

