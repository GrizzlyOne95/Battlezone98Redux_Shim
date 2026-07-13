/*
 * Entry: 0055ba36
 * Name: std::vector<PortData_*,std::allocator<PortData_*>_>::_Ufill
 * Namespace: std::vector<PortData_*,std::allocator<PortData_*>_>
 * Signature: PortData * * _Ufill(vector<PortData_*,std::allocator<PortData_*>_> * this, PortData * * param_1, uint param_2, PortData * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData ** __thiscall
std::vector<PortData_*,std::allocator<PortData_*>_>::_Ufill
          (vector<PortData_*,std::allocator<PortData_*>_> *this,PortData **param_1,uint param_2,
          PortData **param_3)

{
  stdext::unchecked_fill_n<PortData_*_*,unsigned_int,PortData_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
