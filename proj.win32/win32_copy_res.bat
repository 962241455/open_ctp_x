@echo ----------------------------------------------
@echo 修改32/64位目录，支持您的编译选项;默认32；
@echo ----------------------------------------------

xcopy  /y /e /s "..\Resources\*.*" ".\Debug.win32\"  
xcopy  /y /e /s "..\Resources\res\*.*" ".\Debug.win32\res\"  
xcopy  /y /e /s "..\Resources\fonts\*.*" ".\Debug.win32\fonts"  

pause