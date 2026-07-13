
void __fastcall FUN_006e3150(bad_cast *param_1)

{
  *(undefined ***)param_1 =
       boost::exception_detail::error_info_injector<class_std::bad_cast>::vftable;
  *(undefined ***)(param_1 + 0xc) =
       boost::exception_detail::error_info_injector<class_std::bad_cast>::vftable;
  boost::exception::~exception((exception *)(param_1 + 0xc));
  std::bad_cast::~bad_cast(param_1);
  return;
}

