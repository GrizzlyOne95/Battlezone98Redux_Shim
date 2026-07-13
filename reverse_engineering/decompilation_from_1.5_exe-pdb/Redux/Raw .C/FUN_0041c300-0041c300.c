
void FUN_0041c300(undefined4 param_1)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined1 local_e8 [176];
  uint local_38;
  int *local_34;
  uint local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844e43;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = 0;
  local_14 = uVar3;
  FUN_004203f0(param_1,3,1);
  local_8 = 0;
  basic_string<>(uVar3);
  local_8._0_1_ = 1;
  while( true ) {
    local_34 = (int *)FUN_004272a0(local_e8,local_2c,0x7c);
    bVar1 = std::ios_base::operator_bool((ios_base *)((int)local_34 + *(int *)(*local_34 + 4)));
    if (!bVar1) break;
    cVar2 = FUN_00427270(local_2c,"INVERT");
    if (cVar2 == '\0') {
      cVar2 = FUN_00427270(local_2c,&DAT_008712e4);
      if (cVar2 == '\0') {
        cVar2 = FUN_00427270(local_2c,"HANDED");
        if (cVar2 == '\0') {
          cVar2 = FUN_00427270(local_2c,&DAT_008712f4);
          if (cVar2 == '\0') {
            cVar2 = FUN_00427270(local_2c,"BELOW");
            if (cVar2 == '\0') {
              cVar2 = FUN_00427270(local_2c,"ABOVE");
              if (cVar2 == '\0') {
                cVar2 = FUN_00427270(local_2c,"OVERVIEW");
                if (cVar2 == '\0') {
                  cVar2 = FUN_00427270(local_2c,"NOCHECK");
                  if (cVar2 == '\0') {
                    cVar2 = FUN_00427270(local_2c,"ALTCHECK");
                    if (cVar2 != '\0') {
                      local_30 = local_30 | 0x100;
                    }
                  }
                  else {
                    local_30 = local_30 | 0x80;
                  }
                }
                else {
                  local_30 = local_30 | 0x40;
                }
              }
              else {
                local_30 = local_30 | 0x20;
              }
            }
            else {
              local_30 = local_30 | 0x10;
            }
          }
          else {
            local_30 = local_30 | 8;
          }
        }
        else {
          local_30 = local_30 | 4;
        }
      }
      else {
        local_30 = local_30 | 2;
      }
    }
    else {
      local_30 = local_30 | 1;
    }
  }
  local_38 = local_30;
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

