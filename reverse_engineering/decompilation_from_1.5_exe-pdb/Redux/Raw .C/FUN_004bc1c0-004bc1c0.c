
int __fastcall FUN_004bc1c0(_Iterator_base12 *param_1)

{
  _Container_base12 *p_Var1;
  int iVar2;
  
  p_Var1 = std::_Iterator_base12::_Getcont(param_1);
  iVar2 = FUN_004bb930(*(undefined4 *)(param_1 + 8));
  return (*(uint *)(param_1 + 8) % 2) * 6 + *(int *)(*(int *)(p_Var1 + 4) + iVar2 * 4);
}

