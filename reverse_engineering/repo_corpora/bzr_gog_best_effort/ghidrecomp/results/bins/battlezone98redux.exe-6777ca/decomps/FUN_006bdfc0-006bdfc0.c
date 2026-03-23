
bad_alloc * __thiscall FUN_006bdfc0(bad_alloc *param_1,bad_alloc *param_2)

{
  std::bad_alloc::bad_alloc(param_1,param_2);
  *(undefined ***)param_1 = std::length_error::vftable;
  return param_1;
}

