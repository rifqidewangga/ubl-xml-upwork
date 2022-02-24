
@echo off
setx SDK_CONFIG %~dp0config.json /U %USERDOMAIN%/%USERNAME% /S %COMPUTERNAME%


set "CURRENT=%~dp0"

set "_path=%CURRENT%"

for %%a in (%_path:~0,-1%) do set "p2_dir=%%~dpa"\

set p2_dir=%p2_dir:\=\\%

SET XSD=
FOR /F %%I IN ('jq .xsdPath config.json ') DO set "XSD=%%I"

SET XSD_filename=
for %%F in (%XSD%) do  set "XSD_filename=%%~nxF"

SET EN_SCHEMA=
FOR /F %%I IN ('jq .enSchematron config.json ') DO set "EN_SCHEMA=%%I"
SET EN_SCHEMA_filename=
for %%F in (%EN_SCHEMA%) do  set "EN_SCHEMA_filename=%%~nxF"


SET ZATCA_SCHEMA=
FOR /F %%I IN ('jq .zatcaSchematron config.json ') DO set "ZATCA_SCHEMA=%%I"
SET ZATCA_SCHEMA_filename=
for %%F in (%ZATCA_SCHEMA%) do  set "ZATCA_SCHEMA_filename=%%~nxF"

SET CERT=
FOR /F %%I IN ('jq .certPath config.json ') DO set "CERT=%%I"
SET CERT_filename=
for %%F in (%CERT%) do  set "CERT_filename=%%~nxF"

SET PIH=
FOR /F %%I IN ('jq .pihPath config.json ') DO set "PIH=%%I"
SET PIH_filename=
for %%F in (%PIH%) do  set "PIH_filename=%%~nxF"

SET CERT_PASSWORD=
FOR /F %%I IN ('jq .certPassword config.json ') DO set "CERT_PASSWORD=%%I"
SET CERT_PASSWORD_VALUE=
for %%F in (%CERT_PASSWORD%) do  set "CERT_PASSWORD_VALUE=%%~nxF"


echo {	"xsdPath" : "%p2_dir%Data\\Schemas\\xsds\\UBL2.1\\xsd\\maindoc\\%XSD_filename%",  ^
		"enSchematron":"%p2_dir%Data\\Rules\\schematrons\\%EN_SCHEMA_filename%", ^
		"zatcaSchematron":"%p2_dir%Data\\Rules\\schematrons\\%ZATCA_SCHEMA_filename%", ^
		"certPath":"%p2_dir%Data\\Certificates\\%CERT_filename%",^
		"pihPath" : "%p2_dir%Data\\PIH\\%PIH_filename%",^
        "certPassword" : "%CERT_PASSWORD_VALUE%"^
     } > config.json

