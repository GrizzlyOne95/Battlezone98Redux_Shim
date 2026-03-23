
bool __fastcall FUN_00608460(int param_1)

{
  bool bVar1;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    bVar1 = false;
  }
  else {
    bVar1 = Concurrency::_Order_node_base<enum_Concurrency::agent_status>::has_value
                      (*(_Order_node_base<enum_Concurrency::agent_status> **)(param_1 + 0x10));
  }
  return bVar1;
}

