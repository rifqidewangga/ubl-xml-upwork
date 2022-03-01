#pragma once

#include <format>
#include <CkXml.h>
#include <CkStringBuilder.h>
#include "Invoice.h"

class InvoiceGenerator
{
public:
	void Generate(Invoice invoice, std::string filepath);

private:
	CkXml xmlToSign;

	void PopulateXml(Invoice invoice);
	void WriteXMLToFile(std::string path);
};