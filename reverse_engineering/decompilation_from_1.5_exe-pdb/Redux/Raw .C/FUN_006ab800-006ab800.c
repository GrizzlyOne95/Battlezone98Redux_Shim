
bool __thiscall FUN_006ab800(error_condition *param_1,error_condition *param_2)

{
  bool bVar1;
  
  bVar1 = std::error_condition::operator==(param_1,param_2);
  return !bVar1;
}

