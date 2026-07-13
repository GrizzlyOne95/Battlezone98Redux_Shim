
/* Library Function - Single Match
    public: bool __thiscall Concurrency::_Order_node_base<enum
   Concurrency::agent_status>::has_value(void)const 
   
   Libraries: Visual Studio 2012, Visual Studio 2015, Visual Studio 2017, Visual Studio 2019 */

bool __thiscall
Concurrency::_Order_node_base<enum_Concurrency::agent_status>::has_value
          (_Order_node_base<enum_Concurrency::agent_status> *this)

{
  return *(int *)(this + 0x2c0) != 0;
}

