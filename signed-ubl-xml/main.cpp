#include <iostream>

#include <CkXml.h>
#include <CkXmlDSigGen.h>
#include <CkCert.h>
#include <CkStringBuilder.h>
#include <CkXmlDSig.h>

#include "Utility.h"
#include "XMLSigner.h"


int main()
{
    CkXml xmlToSign;
    PopulateSample(xmlToSign);
    WriteXMLToFile(xmlToSign, "../Samples/unsignedDoc.xml");
	
    XMLSigner signer("../Samples/certs/gaztCertificate.p12", "123456789");
    signer.SignXML(xmlToSign, "../Samples/signedDoc.xml");

    //VerifyXML("../Samples/signedDoc.xml");

    return 0;
}