
int __thiscall FUN_004219e0(int param_1,char *param_2,size_t param_3,int param_4)

{
  int iVar1;
  int local_c;
  
  if (*(int *)(param_1 + 0x50) != 0) {
    if ((param_2 == (char *)0x0) && (param_3 == 0 && param_4 == 0)) {
      local_c = 4;
    }
    else {
      local_c = 0;
    }
    iVar1 = setvbuf(*(FILE **)(param_1 + 0x50),param_2,local_c,param_3);
    if (iVar1 == 0) {
      FUN_00423280(*(undefined4 *)(param_1 + 0x50),1);
      return param_1;
    }
  }
  return 0;
}

