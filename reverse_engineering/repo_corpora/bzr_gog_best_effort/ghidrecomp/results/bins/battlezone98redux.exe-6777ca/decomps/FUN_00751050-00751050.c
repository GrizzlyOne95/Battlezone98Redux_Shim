
void FUN_00751050(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_30 [16];
  undefined1 local_20 [20];
  int *local_c;
  undefined1 local_5;
  
  uVar2 = FUN_0073a590(*param_1,param_1[1]);
  cVar1 = FUN_0073a840(uVar2);
  if (cVar1 != '\0') {
    local_5 = *(char *)(param_1 + 4) == '\0';
    local_c = (int *)FUN_006aa1b0();
    uVar2 = (**(code **)(*local_c + 8))(local_20);
    FUN_0073a6e0(uVar2);
    FUN_00578640(local_30,local_5);
  }
  return;
}

