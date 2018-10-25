@ECHO off 
ECHO.
ECHO --- BUILD TRANSFER ---
REM Delete the previous build if it exists
IF EXIST "BO_ZM_Nonhost_Menu.sprx" DEL "BO1Plugin.sprx"
ECHO Deleted old build
REM Rename built SPRX to common name that EBOOT loads
IF EXIST "BO_ZM_Nonhost_Menu.sprx" MOVE "BO_ZM_Nonhost_Menu.sprx" "BO1Plugin.sprx"
ECHO Renamed to BO1Plugin.sprx
REM Open FTP to PS3 and put renamed plugin into tmp directory
"C:\Program Files (x86)\WinSCP\WinSCP.exe" /ini=nul /script="winscpscript.txt"
ECHO Transferred to PS3 tmp directory
ECHO.