
int __thiscall FUN_00700da0(int param_1,type_info *param_2)

{
  bool bVar1;
  int local_8;
  
  bVar1 = type_info::operator==
                    (param_2,(type_info *)
                             &boost::asio::detail::socket_ops::noop_deleter::RTTI_Type_Descriptor);
  if (bVar1) {
    local_8 = param_1 + 0x10;
  }
  else {
    local_8 = 0;
  }
  return local_8;
}

