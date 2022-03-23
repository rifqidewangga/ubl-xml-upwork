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
	CkXmlDSigGen _gen;

	void SetupDSigGen();
	bool LoadCertificate(const char* certPath, const char* certPwd);
	void SaveSbXml(CkStringBuilder& sb, const char* filepath);
	bool VerifyXml(CkStringBuilder& sb);

public:
	XMLSigner(const char* certPath, const char* certPwd);
	bool SignXML(CkXml& doc, const char* filepath);

	~XMLSigner();
};

