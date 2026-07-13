
undefined2 * __thiscall FUN_004bc550(undefined2 *param_1,int param_2)

{
  undefined2 *puVar1;
  ushort *puVar2;
  
  puVar1 = (undefined2 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  puVar2 = (ushort *)FUN_00417780(param_2 + 2);
  *(uint *)(param_1 + 2) = (uint)*puVar2;
  return param_1;
}

