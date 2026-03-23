
void __thiscall FUN_0080f250(_Container_base0 *param_1,_Container_base0 *param_2)

{
  std::_Container_base0::_Swap_all(param_1,param_2);
  _Swap_adl<>(param_1,param_2);
  swap<>(param_1 + 4,param_2 + 4);
  return;
}

