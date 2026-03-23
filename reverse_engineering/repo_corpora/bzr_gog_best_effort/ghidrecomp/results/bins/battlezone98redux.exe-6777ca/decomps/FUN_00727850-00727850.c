
int __fastcall FUN_00727850(_Iterator_base12 *param_1)

{
  _Container_base12 *p_Var1;
  int iVar2;
  
  p_Var1 = std::_Iterator_base12::_Getcont(param_1);
  iVar2 = FUN_00713d00(*(undefined4 *)(param_1 + 8));
  return *(int *)(*(int *)(p_Var1 + 4) + iVar2 * 4) + *(uint *)(param_1 + 8) % 0x10;
}

