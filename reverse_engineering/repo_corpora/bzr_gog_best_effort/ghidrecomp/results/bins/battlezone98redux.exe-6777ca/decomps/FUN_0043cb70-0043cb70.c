
undefined4 FUN_0043cb70(int *param_1,void *param_2,int param_3)

{
  int iVar1;
  void *local_14;
  void *local_10;
  size_t local_c;
  size_t local_8;
  
  if ((((param_1 != (int *)0x0) && (param_2 != (void *)0x0)) && (param_3 != 0)) &&
     (iVar1 = (**(code **)(*param_1 + 0x2c))
                        (param_1,0,param_3,&local_14,&local_c,&local_10,&local_8,0), -1 < iVar1)) {
    memcpy(local_14,param_2,local_c);
    if (local_8 != 0) {
      memcpy(local_10,(void *)((int)param_2 + local_c),local_8);
    }
    (**(code **)(*param_1 + 0x4c))(param_1,local_14,local_c,local_10,local_8);
    return 1;
  }
  return 0;
}

