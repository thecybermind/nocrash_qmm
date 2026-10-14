mkdir package
pushd package
del /q *
rem copy ..\README.md .\
rem copy ..\LICENSE .\

copy ..\bin\Release\x86\nocrash_qmm.dll .\
copy ..\bin\Release\x64\nocrash_qmm_x86_64.dll .\     

popd
