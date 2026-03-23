
/* Library Function - Single Match
    public: void __thiscall boost::exception_detail::refcount_ptr<struct
   boost::exception_detail::error_info_container>::adopt(struct
   boost::exception_detail::error_info_container *)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

void __thiscall
boost::exception_detail::refcount_ptr<struct_boost::exception_detail::error_info_container>::adopt
          (refcount_ptr<struct_boost::exception_detail::error_info_container> *this,
          error_info_container *param_1)

{
  FUN_004499f0();
  *(error_info_container **)this = param_1;
  FUN_00449c60();
  return;
}

