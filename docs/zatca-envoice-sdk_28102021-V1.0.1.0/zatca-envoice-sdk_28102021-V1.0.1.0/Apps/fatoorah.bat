
@echo off

SET VAR=
FOR /F %%I IN ('jq .version %FATOORA_HOME%/global.json') DO set "VAR=%%I"

SET CERT_PASS=
FOR /F %%N IN ('jq .certPassword %FATOORA_HOME%/global.json') DO set "CERT_PASS=%%N"


set "VAR=%VAR:~1,-1%"

set "CERT_PASS=%CERT_PASS:~1,-1%"


if exist "%FATOORA_HOME%/cli-%VAR%-jar-with-dependencies.jar" call java -Dfile.encoding=UTF-8 -jar %FATOORA_HOME%/cli-%VAR%-jar-with-dependencies.jar --globalVersion %VAR% -certpassword %CERT_PASS% %*
