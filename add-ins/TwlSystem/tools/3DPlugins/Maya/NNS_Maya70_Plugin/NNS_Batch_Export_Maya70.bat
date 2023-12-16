set NNS_MAYA_70_APP_ROOT=C:\Program Files\Alias\Maya7.0
set NNS_MAYA_70_N3BE_FILE=%1
"%NNS_MAYA_70_APP_ROOT%\bin\mayabatch.exe" -command "NNS_BatchExport \"$NNS_MAYA_70_N3BE_FILE\""
pause
