
int __thiscall FUN_00416aa0(int param_1,undefined4 param_2)

{
  undefined1 local_28 [4];
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  int local_14;
  int local_10;
  int local_c;
  char local_5;
  
  local_14 = 0;
  local_20 = 0;
  if (*(int *)(param_1 + 4) == 0) {
    local_10 = -0x7ffbfe10;
  }
  else {
    local_c = param_1;
    local_10 = FUN_004394a0(**(undefined4 **)(param_1 + 4),&local_5);
    if (-1 < local_10) {
      if (local_5 == '\0') {
        local_10 = (**(code **)(*(int *)**(undefined4 **)(local_c + 4) + 0x2c))
                             (**(undefined4 **)(local_c + 4),*(undefined4 *)(local_c + 0x20),
                              *(undefined4 *)(local_c + 0x1c),&local_14,&local_1c,&local_20,local_28
                              ,0);
        if (-1 < local_10) {
          if ((local_14 == 0) || (local_20 != 0)) {
            local_10 = -0x7fff0001;
          }
          else {
            FUN_00416970(local_14,local_1c,param_2);
            (**(code **)(*(int *)**(undefined4 **)(local_c + 4) + 0x4c))
                      (**(undefined4 **)(local_c + 4),local_14,local_1c,0,0);
            local_10 = (**(code **)(*(int *)**(undefined4 **)(local_c + 4) + 0x10))
                                 (**(undefined4 **)(local_c + 4),&local_18,0);
            if (-1 < local_10) {
              if (local_18 < *(uint *)(local_c + 0x14)) {
                local_24 = *(int *)(local_c + 8) - *(int *)(local_c + 0x14);
              }
              else {
                local_24 = -*(int *)(local_c + 0x14);
              }
              local_24 = local_24 + local_18;
              *(int *)(local_c + 0x18) = *(int *)(local_c + 0x18) + local_24;
              *(uint *)(local_c + 0x14) = local_18;
              if ((*(int *)(local_c + 0x24) != 0) &&
                 (*(uint *)(local_c + 0x34) <= *(uint *)(local_c + 0x18))) {
                (**(code **)(*(int *)**(undefined4 **)(local_c + 4) + 0x48))
                          (**(undefined4 **)(local_c + 4));
              }
              *(int *)(local_c + 0x20) = *(int *)(local_c + 0x20) + local_1c;
              *(uint *)(local_c + 0x20) = *(uint *)(local_c + 0x20) % *(uint *)(local_c + 8);
              local_10 = 0;
            }
          }
        }
      }
      else {
        local_10 = FUN_00416e10(**(undefined4 **)(local_c + 4),0);
        if (-1 < local_10) {
          local_10 = 0;
        }
      }
    }
  }
  return local_10;
}

