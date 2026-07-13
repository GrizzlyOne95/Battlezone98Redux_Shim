
int __thiscall FUN_006f1970(int param_1,allocator<char> *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  _func_bool_agent_status_ptr **pp_Var3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008550b8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = std::allocator<char>::allocator<char>(param_2);
  uVar2 = FUN_00417780(uVar2,uVar1);
  FUN_006feaa0(uVar2);
  local_8 = 0;
  pp_Var3 = (_func_bool_agent_status_ptr **)FUN_00417780(param_2 + 0x30);
  std::_Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0>::
  _Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0><bool_(__cdecl*const&)(enum_Concurrency::agent_status_const&)>
            ((_Callable_base<bool_(__cdecl*const)(enum_Concurrency::agent_status_const&),0> *)
             (param_1 + 0x30),pp_Var3);
  ExceptionList = local_10;
  return param_1;
}

