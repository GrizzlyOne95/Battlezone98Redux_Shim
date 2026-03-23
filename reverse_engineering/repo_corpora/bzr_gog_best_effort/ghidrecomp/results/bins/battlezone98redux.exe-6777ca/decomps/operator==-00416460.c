
/* Library Function - Single Match
    public: bool __thiscall std::error_condition::operator==(class std::error_condition const
   &)const 
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

bool __thiscall std::error_condition::operator==(error_condition *this,error_condition *param_1)

{
  bool bVar1;
  error_category *peVar2;
  error_category *this_00;
  int iVar3;
  int iVar4;
  
  peVar2 = (error_category *)FUN_00416410();
  this_00 = (error_category *)FUN_00416410();
  bVar1 = error_category::operator==(this_00,peVar2);
  if (bVar1) {
    iVar3 = get();
    iVar4 = get();
    if (iVar3 == iVar4) {
      return true;
    }
  }
  return false;
}

