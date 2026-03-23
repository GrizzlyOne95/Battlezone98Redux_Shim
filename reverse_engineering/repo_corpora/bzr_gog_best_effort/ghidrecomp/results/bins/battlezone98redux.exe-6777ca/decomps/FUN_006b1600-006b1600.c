
undefined4 * __thiscall
FUN_006b1600(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  
  cVar2 = FUN_006b1390(param_3);
  if (cVar2 != '\0') {
    iVar3 = FUN_006b20f0(param_1 + 8,0,0);
    if (iVar3 != 0) {
      FUN_006b0c30(*param_3,param_3 + 4,1);
    }
  }
  FUN_006ae9c0(*param_3,param_3 + 1,0,param_4);
  *param_3 = 0xffffffff;
  *(undefined1 *)(param_3 + 1) = 0;
  std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
            ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(param_3 + 2));
  uVar1 = param_4[1];
  *param_2 = *param_4;
  param_2[1] = uVar1;
  return param_2;
}

