
void FUN_00821310(int param_1,uint param_2,uint param_3)

{
  *(uint *)(*(int *)(param_1 + 8) + 0x5c) =
       ~param_2 & *(uint *)(*(int *)(param_1 + 8) + 0x5c) | param_3 & param_2;
  return;
}

