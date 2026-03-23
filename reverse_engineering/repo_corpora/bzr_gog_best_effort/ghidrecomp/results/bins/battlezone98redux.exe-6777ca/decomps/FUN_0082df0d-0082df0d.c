
undefined4 FUN_0082df0d(undefined4 param_1,int param_2,int param_3)

{
  undefined *puVar1;
  
  puVar1 = (&PTR_PTR_0086f0b4)[*(int *)(param_2 + 8)];
  if (puVar1[2] == (&PTR_PTR_0086f0b4)[*(int *)(param_3 + 8)][2]) {
    FUN_0082df5b(param_1,"attempt to compare two %s values",puVar1);
  }
  else {
    FUN_0082df5b(param_1,"attempt to compare %s with %s",puVar1,
                 (&PTR_PTR_0086f0b4)[*(int *)(param_3 + 8)]);
  }
  return 0;
}

