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
	
    XMLSigner signer;
    signer.SignXML(xmlToSign);

	return 0;
}