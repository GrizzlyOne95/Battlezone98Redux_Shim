
void * FUN_00482540(void *param_1,size_t param_2,char *param_3)

{
  undefined4 local_8;
  
  if (param_2 == 0) {
    local_8 = (void *)0x0;
  }
  else {
    local_8 = memchr(param_1,(int)*param_3,param_2);
  }
  return local_8;
}

