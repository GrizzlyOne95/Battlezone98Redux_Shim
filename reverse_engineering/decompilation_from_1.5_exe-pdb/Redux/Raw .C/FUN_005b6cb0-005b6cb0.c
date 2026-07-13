
void __fastcall FUN_005b6cb0(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x44));
  if (iVar2 == 0) {
    *(undefined4 *)(param_1 + 0x4c) = 3;
  }
  else {
    cVar1 = (**(code **)(**(int **)(param_1 + 0x30) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(param_1 + 0x30) + 0x1c))();
    }
    else {
      *(undefined4 *)(param_1 + 0x4c) = 4;
    }
  }
  return;
}

