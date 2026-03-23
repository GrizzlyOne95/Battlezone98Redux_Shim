
undefined4 * __thiscall FUN_00449f60(undefined4 *param_1,int param_2)

{
  *param_1 = boost::exception::vftable;
  boost::exception_detail::refcount_ptr<struct_boost::exception_detail::error_info_container>::
  refcount_ptr<struct_boost::exception_detail::error_info_container>
            ((refcount_ptr<struct_boost::exception_detail::error_info_container> *)(param_1 + 1),
             (refcount_ptr<struct_boost::exception_detail::error_info_container> *)(param_2 + 4));
  param_1[2] = *(undefined4 *)(param_2 + 8);
  param_1[3] = *(undefined4 *)(param_2 + 0xc);
  param_1[4] = *(undefined4 *)(param_2 + 0x10);
  return param_1;
}

