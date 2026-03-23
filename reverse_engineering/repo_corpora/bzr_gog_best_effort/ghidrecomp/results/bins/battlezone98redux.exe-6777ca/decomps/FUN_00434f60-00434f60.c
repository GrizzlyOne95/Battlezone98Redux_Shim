
void FUN_00434f60(uint param_1,char *param_2)

{
  char cVar1;
  char *local_10;
  char *local_c;
  
  if ((param_1 == 0) || (0x80 < param_1)) {
    FUN_007d6a70("key generated bad scancode %d\n",param_1);
  }
  else {
    local_10 = (char *)(&DAT_008e706c)[param_1];
    local_c = param_2;
    do {
      cVar1 = *local_10;
      *local_c = cVar1;
      local_10 = local_10 + 1;
      local_c = local_c + 1;
    } while (cVar1 != '\0');
  }
  return;
}

