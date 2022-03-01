#pragma once

#include <format>
#include <CkXml.h>
#include <CkStringBuilder.h>
#include "Invoice.h"
#include "XMLSigner.h"

class InvoiceGenerator
{
public:
	InvoiceGenerator(const char* certPath, const char* certPwd);
	void Generate(Invoice invoice, std::string filepath);

private:
	XMLSigner xmlSigner;
	CkXml xmlToSign;

	void PopulateXml(Invoice invoice);
	void WriteXMLToFile(std::string path);
};