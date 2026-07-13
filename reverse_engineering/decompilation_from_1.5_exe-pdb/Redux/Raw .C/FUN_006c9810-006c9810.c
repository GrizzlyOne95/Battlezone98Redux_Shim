
undefined4 __thiscall FUN_006c9810(SchedulerBase *param_1,undefined4 param_2,SchedulerBase *param_3)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 local_c [4];
  SchedulerBase *local_8;
  
  local_8 = param_1;
  bVar1 = Concurrency::details::SchedulerBase::HasWorkPending(param_1);
  if ((!bVar1) && (bVar1 = Concurrency::details::SchedulerBase::HasWorkPending(param_3), !bVar1)) {
    iVar3 = *(int *)local_8 - *(int *)param_3;
    FUN_00447eb0(iVar3);
    FUN_0068f260(iVar3);
    return param_2;
  }
  uVar2 = FUN_00447eb0(*(undefined4 *)param_3);
  puVar4 = local_c;
  FUN_00447eb0(*(int *)local_8);
  FUN_006dc780(puVar4,uVar2);
  uVar2 = FUN_006c97f0();
  FUN_006b26c0(uVar2);
  return param_2;
}

