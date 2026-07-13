
undefined4 * __thiscall FUN_00843bd0(undefined4 *param_1,byte param_2)

{
  *param_1 = boost::system::error_category::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

