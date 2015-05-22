set SCRIPT_DIR=%~dp0
java -Xms512M -Xmx1024M -XX:MaxPermSize=256m -Xdebug -Xrunjdwp:transport=dt_socket,server=y,suspend=n,address=9999 -jar "%SCRIPT_DIR%activator-launch-1.2.10.jar" %*
