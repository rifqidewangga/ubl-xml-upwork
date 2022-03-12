#pragma once

#include <format>
#include <sstream>
#include <iomanip>
#include <CkXml.h>
#include <CkStringBuilder.h>
#include "Invoice.h"
#include "XMLSigner.h"

class InvoiceGenerator
{
public:
	InvoiceGenerator();
	void Generate(Invoice invoice, std::string filepath);

	std::string GetPIH();
	std::string GetQR();

private:
	CkXml xmlToSign;
	CkXml signedXml;

	std::string PIH = "NWZlY2ViNjZmZmM4NmYzOGQ5NTI3ODZjNmQ2OTZjNzljMmRiYzIzOWRkNGU5MWI0NjcyOWQ3M2EyN2ZiNTdlOQ==";
	std::string lastXmlQR;
	
	std::string GetString(double val);

	void PopulateXml(Invoice invoice);
	void PopulateUBLExt();
	void PopulateSupplierPartyInfo();
	void PopulateCustomerPartyInfo();

	void SaveXmlToSign(std::string path);
	void SaveSignedXml(std::string path);

	void SignXML(std::string filename);
	void UpdateLastQR();
	void UpdatePIH();
};