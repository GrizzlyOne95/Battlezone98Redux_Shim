
void __thiscall FUN_0057e7f0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 local_5;
  
  if (*(int *)(param_1 + 4) == *(int *)(param_1 + 8)) {
    FUN_0057f340(1);
  }
  FUN_00422c10(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 4));
  uVar1 = FUN_00417780(param_2);
  uVar2 = *(undefined4 *)(param_1 + 4);
  Getal(&local_5);
  construct<>(uVar2,uVar1);
  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
  return;
}

