#pragma once

#include <string>

struct InvoiceDocumentReference
{
	std::string ID;
};

struct BillingReference
{
	InvoiceDocumentReference InvoiceDocumentReference;
};

struct Invoice
{
	int ID;
	std::string UUID;
	std::string IssueDate;
	std::string IssueTime;
	
	std::string InvoiceTypeCodeAttr;
	int InvoiceTypeCode;
	
	std::string DocumentCurrencyCode;
	std::string TaxCurrencyCode;

	BillingReference BillingReference;
};