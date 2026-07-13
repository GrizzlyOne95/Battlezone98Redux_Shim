
/* Library Function - Single Match
    public: virtual bool __thiscall std::error_category::equivalent(class std::error_code const
   &,int)const 
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

bool __thiscall
std::error_category::equivalent(error_category *this,error_code *param_1,int param_2)

{
  bool bVar1;
  error_category *peVar2;
  int iVar3;
  
  peVar2 = (error_category *)FUN_00416410();
  bVar1 = operator==(this,peVar2);
  if ((bVar1) && (iVar3 = get(), iVar3 == param_2)) {
    return true;
  }
  return false;
}

