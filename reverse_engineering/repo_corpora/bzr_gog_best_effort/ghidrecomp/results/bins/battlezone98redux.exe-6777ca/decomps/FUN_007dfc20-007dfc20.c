
bad_alloc * __thiscall FUN_007dfc20(bad_alloc *param_1,bad_alloc *param_2)

{
  std::bad_alloc::bad_alloc(param_1,param_2);
  *(undefined ***)param_1 = boost::bad_function_call::vftable;
  return param_1;
}

