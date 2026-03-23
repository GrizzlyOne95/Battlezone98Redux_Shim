
void FUN_00690a40(undefined4 *param_1)

{
  undefined4 *puVar1;
  int local_c;
  
  if (-1 < (int)param_1[1]) {
    if ((*(int *)(&DAT_00945188 + param_1[1] * 4) << 0x10) >> 0x18 < 1) {
      if ((char)*(undefined4 *)(&DAT_00945188 + param_1[1] * 4) < '\x01') {
        return;
      }
      local_c = 1;
    }
    else {
      local_c = 0;
    }
    puVar1 = malloc(8);
    *puVar1 = param_1[2];
    puVar1[1] = param_1[3];
    FUN_0069d330((&DAT_02bfdff0)[local_c],puVar1);
    FUN_006a5fd0("resource #%d found at (%d, %d) id number %d type %d addr %08x\n",local_c,*puVar1,
                 puVar1[1],*param_1,param_1[1],puVar1);
  }
  return;
}

