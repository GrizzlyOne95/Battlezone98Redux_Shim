
void __fastcall FUN_00418850(int param_1)

{
  undefined4 *puVar1;
  char cVar2;
  undefined4 *puVar3;
  
  cVar2 = FUN_004187f0();
  if ((cVar2 != '\0') && (*(int *)(param_1 + 0x18) != 0)) {
    puVar1 = *(undefined4 **)(param_1 + 0x18);
    puVar3 = (undefined4 *)FUN_00421d30(param_1);
    *puVar3 = *puVar1;
  }
  return;
}

