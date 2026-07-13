
int FUN_00417a10(void *param_1,void *param_2,size_t param_3)

{
  undefined4 local_8;
  
  if (param_3 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = memcmp(param_1,param_2,param_3);
  }
  return local_8;
}

