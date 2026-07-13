
bool FUN_00759eb0(void *param_1,void *param_2)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = memcmp(param_1,param_2,0x10);
  if (iVar1 < 0) {
    bVar2 = true;
  }
  else if (iVar1 < 1) {
    bVar2 = *(uint *)((int)param_1 + 0x10) < *(uint *)((int)param_2 + 0x10);
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}

