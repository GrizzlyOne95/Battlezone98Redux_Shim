
void __fastcall FUN_006b40d0(int param_1)

{
  char cVar1;
  
  FUN_006ac0d0();
  FUN_006d8a70(*(int *)(param_1 + 4) + 0x3c);
  cVar1 = FUN_004c85a0();
  *(bool *)(*(int *)(param_1 + 4) + 0x38) = cVar1 == '\0';
  FUN_006ac0f0();
  if (cVar1 == '\0') {
    FUN_006acd90(*(undefined4 *)(param_1 + 4),1);
  }
  return;
}

