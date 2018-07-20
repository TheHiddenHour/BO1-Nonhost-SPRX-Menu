if exist "BO1_ZM_Nonhost_HUDs.sprx" DEL "BO1Plugin.sprx"
MOVE "BO1_ZM_Nonhost_HUDs.sprx" "BO1Plugin.sprx"

DEL "winscplog.txt"
"C:\Program Files (x86)\WinSCP\winscp.exe" /console /script="winscpscript.txt" /log="winscplog.txt"