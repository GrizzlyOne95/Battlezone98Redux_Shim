
/* Library Function - Single Match
    public: void __thiscall Concurrency::details::CollectionTypes::Count::Decrement(void)
   
   Library: Visual Studio */

void __thiscall Concurrency::details::CollectionTypes::Count::Decrement(Count *this)

{
  *(int *)this = *(int *)this + -1;
  return;
}

