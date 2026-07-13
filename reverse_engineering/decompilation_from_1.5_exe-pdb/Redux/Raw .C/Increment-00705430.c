
/* Library Function - Single Match
    public: void __thiscall Concurrency::details::CollectionTypes::Count::Increment(void)
   
   Library: Visual Studio */

void __thiscall Concurrency::details::CollectionTypes::Count::Increment(Count *this)

{
  *(int *)this = *(int *)this + 1;
  return;
}

