
void __thiscall FUN_006acbe0(undefined4 *param_1,undefined4 param_2)

{
  int *local_8;
  
  for (local_8 = (int *)*param_1; local_8 != (int *)0x0; local_8 = (int *)local_8[1]) {
    (**(code **)(*local_8 + 0x10))(param_2);
  }
  return;
}

