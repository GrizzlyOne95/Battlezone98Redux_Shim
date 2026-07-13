
void __fastcall FUN_005fcb40(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x6c))();
  if ((cVar1 != '\0') && (*(int *)(*(int *)(param_1 + 0x34) + 0xac) == 7)) {
    FUN_004dbc00();
  }
  puVar2 = (undefined4 *)FUN_00462490();
  uVar3 = FUN_0045c460(*puVar2,puVar2[1],puVar2[2]);
  (**(code **)(**(int **)(param_1 + 0x34) + 0x8c))(uVar3);
  (**(code **)(**(int **)(param_1 + 0x34) + 0x88))(0);
  return;
}

