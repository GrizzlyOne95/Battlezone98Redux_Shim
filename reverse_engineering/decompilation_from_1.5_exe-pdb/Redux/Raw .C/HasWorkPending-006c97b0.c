
/* Library Function - Single Match
    protected: virtual bool __thiscall Concurrency::details::SchedulerBase::HasWorkPending(void)
   
   Library: Visual Studio 2010 Debug */

bool __thiscall Concurrency::details::SchedulerBase::HasWorkPending(SchedulerBase *this)

{
  char cVar1;
  
  cVar1 = FUN_006ce2b0();
  if ((cVar1 == '\0') && (cVar1 = FUN_006ce2d0(), cVar1 == '\0')) {
    return false;
  }
  return true;
}

