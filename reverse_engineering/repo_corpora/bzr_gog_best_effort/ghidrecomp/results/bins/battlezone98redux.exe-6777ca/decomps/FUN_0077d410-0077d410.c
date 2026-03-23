
float10 __thiscall FUN_0077d410(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  ushort *puVar1;
  
  puVar1 = (ushort *)FUN_00492d60(param_2,param_3,param_1);
  return (float10)((float)(*puVar1 & 0xfff) * 0.02);
}

