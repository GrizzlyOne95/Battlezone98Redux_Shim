
int __thiscall FUN_006fb8d0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  _func_bool_agent_status_ptr **pp_Var3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855bd8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_00417780(param_4,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar2 = FUN_00417780(param_3,uVar1);
  FUN_0070bc00(uVar2,uVar1);
  local_8 = 0;
  pp_Var3 = (_func_bool_agent_status_ptr **)FUN_00417780(param_2);
  std::_Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0>::
  _Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0><bool_(__cdecl*const&)(enum_Concurrency::agent_status_const&)>
            ((_Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0> *)
             (param_1 + 0xc),pp_Var3);
  ExceptionList = local_10;
  return param_1;
}

