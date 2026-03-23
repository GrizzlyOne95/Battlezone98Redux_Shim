
void __fastcall FUN_00474260(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x1c) != *(int *)(param_1 + 0x18)) {
    FUN_00474720();
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x1c);
    FUN_00474300();
  }
  uVar2 = FUN_00473890();
  cVar1 = FUN_00474b80(uVar2);
  if (cVar1 != '\0') {
    FUN_00474720();
    uVar2 = FUN_004dbb40();
    FUN_00474ee0(uVar2);
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x1c);
    FUN_00474300();
  }
  FUN_00474860();
  return;
}

