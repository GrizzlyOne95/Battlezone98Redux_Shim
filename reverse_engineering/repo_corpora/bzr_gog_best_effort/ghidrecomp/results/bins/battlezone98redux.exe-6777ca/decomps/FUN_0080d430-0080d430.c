
/* WARNING: Removing unreachable block (ram,0x0080d5c9) */
/* WARNING: Removing unreachable block (ram,0x0080d501) */

undefined4 FUN_0080d430(undefined4 *param_1,undefined4 param_2,__ExceptionPtr *param_3)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined8 uVar4;
  double local_40;
  double local_38;
  double local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  undefined1 local_7;
  char local_6;
  char local_5;
  
  cVar1 = FID_conflict_operator__();
  if (cVar1 == '\0') {
    local_c = *param_1;
    local_7 = FUN_0080e330(param_1,param_2);
    uVar4 = 0;
    local_20 = 0;
    local_5 = FUN_0080e350(param_1,param_2,&local_20);
    if ((local_5 == '\0') &&
       ((cVar1 = FUN_0080e370(param_1,param_2,&local_28), cVar1 != '\0' ||
        (cVar1 = FUN_0080e470(param_1,param_2,&local_28), cVar1 != '\0')))) {
      fVar3 = (float10)FUN_007fb050(local_7,local_28);
      local_30 = (double)fVar3;
      std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                ((shared_ptr<class___ExceptionPtr> *)&local_30,param_3);
      uVar2 = 1;
    }
    else {
      local_6 = 0;
      FUN_00423890();
      local_10 = 0;
      cVar1 = FUN_0080e540(param_1,param_2);
      if (cVar1 == '\0') {
        if (local_5 == '\0') {
          *param_1 = local_c;
          return 0;
        }
        local_14 = *param_1;
        local_6 = FUN_0080e5f0(param_1,param_2);
      }
      else {
        cVar1 = FUN_0080e580(param_1,param_2,&local_20,&local_10);
        if ((cVar1 == '\0') && (local_5 == '\0')) {
          *param_1 = local_c;
          return 0;
        }
        local_14 = *param_1;
        local_6 = FUN_0080e5f0(param_1,param_2);
      }
      if (local_6 == '\0') {
        if (local_10 == 0) {
          cVar1 = FUN_0080e7c0();
          if (cVar1 == '\0') {
            FUN_008448ce();
            local_28 = uVar4;
          }
          else {
            cVar1 = FUN_0080e370(param_1,param_2,&local_28);
            if ((cVar1 != '\0') || (cVar1 = FUN_0080e470(param_1,param_2,&local_28), cVar1 != '\0'))
            {
              fVar3 = (float10)FUN_007fb050(local_7,local_28);
              local_38 = (double)fVar3;
              std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                        ((shared_ptr<class___ExceptionPtr> *)&local_38,param_3);
              return 1;
            }
            FUN_008448ce();
            local_28 = uVar4;
          }
        }
        else {
          FUN_0080e680(-local_10,&local_28,(undefined4)local_20,(int)((ulonglong)local_20 >> 0x20));
        }
      }
      else {
        local_18 = 0;
        cVar1 = FUN_0080e640(param_1,param_2,&local_18);
        if (cVar1 == '\0') {
          *param_1 = local_14;
          FUN_008448ce();
          local_28 = uVar4;
        }
        else {
          cVar1 = FUN_0080e660(local_18,local_10,&local_28,(undefined4)local_20,
                               (int)((ulonglong)local_20 >> 0x20));
          if (cVar1 == '\0') {
            return 0;
          }
        }
      }
      fVar3 = (float10)FUN_007fb050(local_7,local_28);
      local_40 = (double)fVar3;
      std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
                ((shared_ptr<class___ExceptionPtr> *)&local_40,param_3);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

