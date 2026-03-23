
uint FUN_0082ecf4(uint *param_1,void *param_2,uint param_3)

{
  int iVar1;
  uint _Size;
  
  while( true ) {
    if (param_3 == 0) {
      return 0;
    }
    iVar1 = FUN_0082ec83(param_1);
    if (iVar1 == -1) break;
    _Size = *param_1;
    if (param_3 <= *param_1) {
      _Size = param_3;
    }
    memcpy(param_2,(void *)param_1[1],_Size);
    *param_1 = *param_1 - _Size;
    param_1[1] = param_1[1] + _Size;
    param_2 = (void *)((int)param_2 + _Size);
    param_3 = param_3 - _Size;
  }
  return param_3;
}

