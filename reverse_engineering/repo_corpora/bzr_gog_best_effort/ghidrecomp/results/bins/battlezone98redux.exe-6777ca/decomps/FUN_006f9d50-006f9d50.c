
shared_ptr<struct__EXCEPTION_RECORD_const_> * __thiscall
FUN_006f9d50(shared_ptr<struct__EXCEPTION_RECORD_const_> *param_1,undefined4 param_2,
            undefined4 param_3)

{
  shared_ptr<struct__EXCEPTION_RECORD_const_> *psVar1;
  _func_bool_agent_status_ptr **pp_Var2;
  
  psVar1 = (shared_ptr<struct__EXCEPTION_RECORD_const_> *)FUN_00417780(param_3);
  std::shared_ptr<struct__EXCEPTION_RECORD_const_>::shared_ptr<struct__EXCEPTION_RECORD_const_>
            (param_1,psVar1);
  pp_Var2 = (_func_bool_agent_status_ptr **)FUN_00417780(param_2);
  std::_Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0>::
  _Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0><bool_(__cdecl*const&)(enum_Concurrency::agent_status_const&)>
            ((_Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0> *)
             (param_1 + 4),pp_Var2);
  return param_1;
}

