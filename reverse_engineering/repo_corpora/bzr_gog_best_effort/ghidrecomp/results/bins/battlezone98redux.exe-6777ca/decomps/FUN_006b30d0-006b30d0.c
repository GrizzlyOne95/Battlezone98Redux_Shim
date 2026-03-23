
undefined1 FUN_006b30d0(void *param_1,void *param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = memcmp(param_1,param_2,0x10);
  if ((iVar2 == 0) && (*(int *)((int)param_1 + 0x10) == *(int *)((int)param_2 + 0x10))) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

