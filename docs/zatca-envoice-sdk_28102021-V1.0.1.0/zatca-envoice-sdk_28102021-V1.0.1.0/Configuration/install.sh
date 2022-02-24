
SDK_CONFIG="${PWD}/config.json"
#echo $SDK_CONFIG
export SDK_CONFIG=$SDK_CONFIG

parentDir="$(dirname "$PWD")"

xsdPath=$(jq -r '.xsdPath' config.json)
xsdPathFileName="$(basename $xsdPath)"

enSchematron=$(jq -r '.enSchematron' config.json)
enSchematronFileName="$(basename $enSchematron)"

zatcaSchematron=$(jq -r '.zatcaSchematron' config.json)
zatcaSchematronFileName="$(basename $zatcaSchematron)"

certPath=$(jq -r '.certPath' config.json)
certPathFileName="$(basename $certPath)"

pihPath=$(jq -r '.pihPath' config.json)
pihPathFileName="$(basename $pihPath)"

certPassword=$(jq -r '.certPassword' config.json)
certPasswordValue="$(basename $certPassword)"


jq -n '{"xsdPath":$one, "enSchematron":$two, "zatcaSchematron":$thr,"certPath":$fou ,"pihPath":$fiv ,"certPassword":$six}' \
  --arg one "${parentDir}/Data/Schemas/xsds/UBL2.1/xsd/maindoc/$xsdPathFileName" \
  --arg two "${parentDir}/Data/Rules/schematrons/$enSchematronFileName"   \
  --arg thr "${parentDir}/Data/Rules/schematrons/$zatcaSchematronFileName" \
  --arg fou "${parentDir}/Data/Certificates/$certPathFileName" \
  --arg fiv "${parentDir}/Data/PIH/$pihPathFileName"  \
  --arg six "$certPasswordValue" >config.json

