
int __thiscall FUN_0042df40(int *param_1,void *param_2,uint param_3)

{
  char cVar1;
  int iVar2;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  void *local_20;
  uint local_1c;
  int local_18;
  int local_14;
  void *local_10;
  int *local_c;
  char local_5;
  
  local_c = param_1;
  FUN_00430600((char)param_1[7]);
  if ((((char)local_c[7] != '\0') && (2 < param_3)) &&
     (iVar2 = memcmp(param_2,&PTR_DAT_0087152c,3), iVar2 == 0)) {
    param_2 = (void *)((int)param_2 + 3);
    param_3 = param_3 - 3;
  }
  if (param_3 == 0) {
    local_14 = 0;
  }
  else {
    local_18 = FUN_00430620(param_2,param_3);
    if (local_18 == -1) {
      local_14 = -1;
    }
    else {
      local_10 = (void *)FUN_0083e9fc(local_18 + 1,&DAT_00914ce1);
      if (local_10 == (void *)0x0) {
        local_14 = -2;
      }
      else {
        memset(local_10,0,local_18 + 1);
        cVar1 = FUN_00430630(param_2,param_3,local_10,local_18);
        if (cVar1 == '\0') {
          operator_delete__(local_10);
          local_14 = -1;
        }
        else {
          local_20 = local_10;
          local_30 = &DAT_008a1ad8;
          local_2c = 0;
          local_28 = 0;
          local_24 = 0;
          local_5 = *local_c != 0;
          local_1c = (uint)(byte)local_5;
          local_14 = FUN_00430c50(&local_20,local_1c);
          while (-1 < local_14) {
            cVar1 = FUN_00430cc0(&local_20,&local_30,&local_2c,&local_28,&local_24);
            if (cVar1 == '\0') {
              if (local_5 == '\0') {
                *local_c = (int)local_10;
                local_c[1] = local_18 + 1;
              }
              else {
                operator_delete__(local_10);
              }
              return 0;
            }
            local_14 = FUN_00426e30(local_30,local_2c,local_28,local_24,0,local_5);
          }
        }
      }
    }
  }
  return local_14;
}

