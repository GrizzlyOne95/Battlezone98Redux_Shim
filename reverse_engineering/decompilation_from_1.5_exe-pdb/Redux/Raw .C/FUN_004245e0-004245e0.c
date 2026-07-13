
void __thiscall FUN_004245e0(_Container_base0 *param_1,_Container_base0 *param_2)

{
  undefined4 uVar1;
  undefined1 local_5;
  
  std::_Container_base0::_Swap_all(param_1,param_2);
  uVar1 = FUN_00422f60(&local_5);
  FUN_004178a0(uVar1);
  _Swap_adl<>(param_1,param_2);
  swap<>(param_1 + 4,param_2 + 4);
  return;
}

