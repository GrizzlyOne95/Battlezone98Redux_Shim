
bool __thiscall FUN_006ab710(error_category *param_1,error_category *param_2)

{
  bool bVar1;
  
  bVar1 = std::error_category::operator==(param_1,param_2);
  return !bVar1;
}

