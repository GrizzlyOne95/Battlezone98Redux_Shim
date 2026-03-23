
exception * __fastcall FUN_006ab2c0(exception *param_1)

{
  char *local_c;
  exception *local_8;
  
  local_c = "bad allocation";
  local_8 = param_1;
  std::exception::exception(param_1,&local_c,1);
  *(undefined ***)local_8 = std::bad_alloc::vftable;
  return local_8;
}

