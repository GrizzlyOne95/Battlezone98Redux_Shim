
int __thiscall FUN_00586200(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_00417780(param_2);
  FUN_00586240(uVar1);
  puVar2 = (undefined4 *)FUN_00417780(param_2 + 4);
  *(undefined4 *)(param_1 + 4) = *puVar2;
  return param_1;
}

