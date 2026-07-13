
void __thiscall FUN_006f01a0(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  
  piVar1 = (int *)FUN_00416410(param_1);
  iVar2 = get();
  uVar3 = (**(code **)(*piVar1 + 4))(0x3a);
  uVar3 = FUN_004bc590(param_2,uVar3);
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006d9650(uVar3);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,iVar2);
  return;
}

