rd .\release_bat /q /s
del .\release_bat*

mkdir .\release_bat
mkdir .\release_bat\Input
mkdir .\release_bat\MyResource
mkdir .\release_bat\App
mkdir .\release_bat\dll
mkdir .\release_bat\Output

copy .\Input\*.* .\release_bat\Input
copy .\MyResource\*.* .\release_bat\MyResource
copy .\Release\*.* .\release_bat\App
copy .\dll\*.* .\release_bat\dll
copy .\otherdll\*.* .\release_bat\dll
copy .\cpdll.bat .\release_bat\
copy .\rmdll.bat .\release_bat\
copy .\Readme.txt .\release_bat\