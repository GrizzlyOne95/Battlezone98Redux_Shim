
void __fastcall FUN_00438690(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  
  while( true ) {
    cVar1 = FUN_0042d8f0();
    if (cVar1 != '\0') break;
    puVar2 = (undefined4 *)FUN_00438b60();
    puVar2 = (undefined4 *)*puVar2;
    iVar3 = FUN_0043acd0(*puVar2);
    if (iVar3 != 0) {
      FUN_0043aaa0(iVar3);
    }
    operator_delete(puVar2);
    FUN_00438bb0();
  }
  *(undefined1 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x30) = 1;
  *(undefined1 *)(param_1 + 0x40) = 0;
  return;
}

