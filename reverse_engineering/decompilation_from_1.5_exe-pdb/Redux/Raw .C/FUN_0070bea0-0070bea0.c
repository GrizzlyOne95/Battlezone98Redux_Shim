
int __thiscall FUN_0070bea0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  uVar1 = FUN_00417780(param_2);
  FUN_006cc200(uVar1);
  puVar2 = (undefined1 *)FUN_00417780(param_3);
  *(undefined1 *)(param_1 + 4) = *puVar2;
  return param_1;
}

