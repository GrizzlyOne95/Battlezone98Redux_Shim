
undefined4 FUN_006ac330(int *param_1,int *param_2)

{
  bool bVar1;
  undefined4 uVar2;
  
  if (((param_1[1] == 0) || (param_2[1] == 0)) || (param_1[1] != param_2[1])) {
    if (((*param_1 != 0) && (*param_2 != 0)) &&
       (bVar1 = type_info::operator==((type_info *)*param_1,(type_info *)*param_2), bVar1)) {
      return 1;
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

