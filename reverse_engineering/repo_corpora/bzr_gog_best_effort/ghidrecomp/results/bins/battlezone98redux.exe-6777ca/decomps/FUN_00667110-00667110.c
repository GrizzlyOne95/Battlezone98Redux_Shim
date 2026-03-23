
int * __thiscall FUN_00667110(int *param_1,int *param_2)

{
  *param_1 = *param_2;
  if (*param_1 != 0) {
    std::_Ref_count_base::_Incref((_Ref_count_base *)*param_1);
  }
  return param_1;
}

