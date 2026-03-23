
void __fastcall FUN_006a6400(int param_1)

{
  int iVar1;
  undefined1 local_5;
  
  iVar1 = *(int *)(param_1 + 4) + -8;
  Getal(&local_5);
  destroy<>(iVar1);
  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -8;
  return;
}

