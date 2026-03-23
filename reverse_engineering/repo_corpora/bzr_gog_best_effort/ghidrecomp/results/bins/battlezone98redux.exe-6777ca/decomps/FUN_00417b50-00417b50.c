
void __fastcall FUN_00417b50(int *param_1)

{
  undefined4 *puVar1;
  
  if ((*param_1 != 0) &&
     (puVar1 = (undefined4 *)(**(code **)(*(int *)*param_1 + 8))(), puVar1 != (undefined4 *)0x0)) {
    (**(code **)*puVar1)(1);
  }
  return;
}

