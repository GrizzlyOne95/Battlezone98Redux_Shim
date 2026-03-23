
void __fastcall FUN_004bc0f0(_Container_base12 *param_1)

{
  FUN_00417460();
  std::_Container_base12::_Orphan_all(param_1);
  destroy<>(*(undefined4 *)param_1);
  deallocate(*(undefined4 *)param_1,1);
  *(undefined4 *)param_1 = 0;
  return;
}

