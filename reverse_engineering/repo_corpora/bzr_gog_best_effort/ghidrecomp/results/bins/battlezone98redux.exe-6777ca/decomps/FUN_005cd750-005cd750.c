
bool __thiscall FUN_005cd750(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  _Order_node_base<enum_Concurrency::agent_status> *this;
  
  this = (_Order_node_base<enum_Concurrency::agent_status> *)FUN_00462630(param_2,param_1);
  if (this == (_Order_node_base<enum_Concurrency::agent_status> *)0x0) {
    bVar1 = false;
  }
  else {
    bVar1 = Concurrency::_Order_node_base<enum_Concurrency::agent_status>::has_value(this);
  }
  return bVar1;
}

