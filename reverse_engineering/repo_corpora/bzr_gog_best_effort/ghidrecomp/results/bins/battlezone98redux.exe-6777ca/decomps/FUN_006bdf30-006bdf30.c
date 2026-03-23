
bad_alloc * __thiscall FUN_006bdf30(bad_alloc *param_1,bad_alloc *param_2)

{
  std::bad_alloc::bad_alloc(param_1,param_2);
  *(undefined ***)param_1 = std::out_of_range::vftable;
  return param_1;
}

