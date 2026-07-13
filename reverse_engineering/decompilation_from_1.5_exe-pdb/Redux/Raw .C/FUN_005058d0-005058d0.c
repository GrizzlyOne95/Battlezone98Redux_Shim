
undefined4 FUN_005058d0(int *param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  void *_Src;
  undefined4 uVar1;
  uint local_8;
  
  _Src = (void *)FUN_0082d377(param_3,param_4,&local_8);
  if (local_8 < 0x1f) {
    if (*param_1 + local_8 < param_2) {
      *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + (char)local_8;
      memcpy((void *)*param_1,_Src,local_8);
      *param_1 = *param_1 + local_8;
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else if (*param_1 + 1 + local_8 < param_2) {
    *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + '\x1f';
    *(char *)*param_1 = (char)local_8;
    *param_1 = *param_1 + 1;
    memcpy((void *)*param_1,_Src,local_8);
    *param_1 = *param_1 + local_8;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

