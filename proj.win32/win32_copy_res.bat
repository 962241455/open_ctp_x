@echo ----------------------------------------------
@echo �޸�32/64λĿ¼��֧�����ı���ѡ��;Ĭ��32��
@echo ----------------------------------------------

xcopy  /y /e /s "..\Resources\*.*" ".\Debug.win32\"  
xcopy  /y /e /s "..\Resources\res\*.*" ".\Debug.win32\res\"  
xcopy  /y /e /s "..\Resources\fonts\*.*" ".\Debug.win32\fonts"  

pause