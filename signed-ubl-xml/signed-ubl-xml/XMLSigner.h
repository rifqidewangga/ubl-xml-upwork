#pragma once

#include <iostream>

#include <CkXml.h>
#include <CkXmlDSigGen.h>
#include <CkCert.h>
#include <CkStringBuilder.h>
#include <CkXmlDSig.h>


class XMLSigner
{
private:
	CkCert _cert;
	const char* _certPath = "../Samples/certs/sample.pfx";
	const char* _certPwd = "pfxPassword";
	CkXmlDSigGen _gen;

	void SetupDSigGen();
	bool LoadCertificate();
	void SaveSbXml(CkStringBuilder& sb, const char* filepath);
	bool VerifyXml(CkStringBuilder& sb);

public:
	bool SignXML(CkXml& doc);
};

