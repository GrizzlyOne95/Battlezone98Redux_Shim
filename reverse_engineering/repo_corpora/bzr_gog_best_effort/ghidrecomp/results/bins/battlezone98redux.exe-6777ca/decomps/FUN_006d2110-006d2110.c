
undefined4 __thiscall FUN_006d2110(SchedulerBase *param_1,undefined4 param_2)

{
  bool bVar1;
  undefined4 uVar2;
  undefined1 local_14 [8];
  undefined4 local_c;
  SchedulerBase *local_8;
  
  local_8 = param_1;
  bVar1 = Concurrency::details::SchedulerBase::HasWorkPending(param_1);
  if (bVar1) {
    uVar2 = FUN_006d1b40();
    FUN_006b27e0(uVar2);
  }
  else {
    local_c = FUN_006d5500();
    FUN_006d92d0(local_14,local_c);
    FUN_006b27c0(local_14);
  }
  return param_2;
}

