
int __thiscall FUN_006f9c30(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  _func_bool_agent_status_ptr **pp_Var3;
  
  uVar1 = FUN_00417780(param_4);
  uVar2 = FUN_00417780(param_3,uVar1);
  FUN_006f9ce0(uVar2,uVar1);
  pp_Var3 = (_func_bool_agent_status_ptr **)FUN_00417780(param_2);
  std::_Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0>::
  _Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0><bool_(__cdecl*const&)(enum_Concurrency::agent_status_const&)>
            ((_Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0> *)
             (param_1 + 4),pp_Var3);
  return param_1;
}

