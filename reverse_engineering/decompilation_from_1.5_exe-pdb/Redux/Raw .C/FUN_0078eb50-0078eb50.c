
void __fastcall FUN_0078eb50(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((*(int *)(param_1 + 0x170) != 0) && (*(int *)(param_1 + 0x174) != 0)) {
    piVar1 = (int *)FUN_007647a0();
    iVar2 = (**(code **)(*piVar1 + 0x20))();
    (**(code **)(**(int **)(param_1 + 0x174) + 0x3c))(&DAT_008a1ad8);
    if (iVar2 == 3) {
      uVar3 = FUN_0081cb40(&DAT_0089df3c,"multi_player");
      FUN_007c2950(uVar3);
      FUN_007c3040(1);
    }
    else {
      uVar3 = FUN_0081cb40("multi_common","not ready");
      FUN_007c2950(uVar3);
      FUN_007c3040(0);
      if (iVar2 == 1) {
        uVar3 = FUN_0081cb40("multi_message","no inet");
        (**(code **)(**(int **)(param_1 + 0x174) + 0x3c))(uVar3);
      }
      else if (iVar2 == 2) {
        uVar3 = FUN_0081cb40("multi_message","no auth");
        (**(code **)(**(int **)(param_1 + 0x174) + 0x3c))(uVar3);
      }
    }
  }
  return;
}

