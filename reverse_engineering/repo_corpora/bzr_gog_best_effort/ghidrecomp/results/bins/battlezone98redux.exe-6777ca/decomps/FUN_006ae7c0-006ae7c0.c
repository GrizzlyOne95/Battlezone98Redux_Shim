
void __thiscall FUN_006ae7c0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < *(uint *)*param_1; local_8 = local_8 + 1) {
    FUN_006c9300(*(undefined4 *)(*param_1 + 4 + local_8 * 4),param_3);
  }
  return;
}

