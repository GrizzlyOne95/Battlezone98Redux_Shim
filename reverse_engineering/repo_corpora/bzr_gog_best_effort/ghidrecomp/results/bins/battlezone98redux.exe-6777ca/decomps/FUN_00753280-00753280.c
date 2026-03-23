
undefined4 __fastcall FUN_00753280(_Iterator_base12 *param_1)

{
  _Container_base12 *p_Var1;
  int iVar2;
  
  p_Var1 = std::_Iterator_base12::_Getcont(param_1);
  iVar2 = FUN_007485a0(*(undefined4 *)(param_1 + 8));
  return *(undefined4 *)(*(int *)(p_Var1 + 4) + iVar2 * 4);
}

